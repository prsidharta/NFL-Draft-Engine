import nflreadpy as nfl
import polars as pl
import os
import csv
import boto3
import time 
from botocore.exceptions import NoCredentialsError

draft_year = int(input("Enter Draft Year: "))
season = draft_year - 1

print(f"Loading data for the {season} season...")
pbp = nfl.load_pbp([season])

plays = pbp.filter(
    pl.col('play_type').is_in(['pass', 'run']) & 
    pl.col('posteam').is_not_null() & 
    pl.col('defteam').is_not_null()
)

start_time = time.time()

num_rows = plays.height
print(f"\nProcessed {num_rows} rows of play-by-play data.")

offense_data = plays.group_by(['posteam', 'play_type']).agg(pl.col('epa').mean()).to_dicts()
defense_data = plays.group_by(['defteam', 'play_type']).agg(pl.col('epa').mean()).to_dicts()

off_records = {}
for row in offense_data:
    team = row['posteam']
    if team not in off_records: off_records[team] = {}
    off_records[team][row['play_type']] = row['epa']

def_records = {}
for row in defense_data:
    team = row['defteam']
    if team not in def_records: def_records[team] = {}
    def_records[team][row['play_type']] = row['epa']

needs_dict = {}
for team, off_stats in off_records.items():
    if team not in def_records:
        continue
        
    def_stats = def_records[team]
    
    if 'pass' not in off_stats or 'run' not in off_stats or 'pass' not in def_stats or 'run' not in def_stats:
        continue

    weaknesses = {
        'QB': off_stats['pass'],
        'WR': off_stats['pass'] + 0.01,
        'OL': (off_stats['run'] + off_stats['pass']) / 2,
        'RB': off_stats['run'],
        'CB': -def_stats['pass'],
        'S': -def_stats['pass'] + 0.01,
        'DE': -def_stats['pass'] + 0.02,
        'LB': -def_stats['run'],
        'DT': -def_stats['run'] + 0.01
    }
    
    sorted_needs = sorted(weaknesses, key=weaknesses.get)[:3]
    needs_dict[team] = sorted_needs

os.makedirs('data', exist_ok=True)
filepath = f'data/{draft_year}_needs.csv'
filename = f"{draft_year}_needs.csv"

with open(filepath, 'w', newline='') as f:
    writer = csv.writer(f)
    for team, needs in needs_dict.items():
        writer.writerow([team] + needs)

processing_time = time.time() - start_time
print(f"Successfully generated {filepath} locally!")
print(f"Calculated EPA and generated team needs in {processing_time:.4f} seconds.\n")

AWS_BUCKET_NAME = 'psidharta-nfl-redraft-data' 

s3 = boto3.client('s3')

try:
    print(f"Uploading {filename} to AWS S3 Bucket: '{AWS_BUCKET_NAME}'...")
    aws_start = time.time()
    
    s3.upload_file(filepath, AWS_BUCKET_NAME, filename)
    
    aws_time = time.time() - aws_start
    print(f"Uploaded data to AWS (Upload took {aws_time:.4f} seconds).")
except NoCredentialsError:
    print("Warning: AWS Credentials not found on this machine. File saved locally only.")
except Exception as e:
    print(f"AWS Upload Failed: {e}. File saved locally only.")