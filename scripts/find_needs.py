import nflreadpy as nfl
import pandas as pd
import os

draft_year = int(input("Enter Draft Year: "))
season = draft_year - 1

pbp = nfl.import_pbp_data([season])

offense = pbp[pbp['play_type'].isin(['pass', 'run'])].groupby(['posteam', 'play_type'])['epa'].mean().unstack()
defense = pbp[pbp['play_type'].isin(['pass', 'run'])].groupby(['defteam', 'play_type'])['epa'].mean().unstack()

needs_dict = {}
for team in offense.index:
    if team not in defense.index:
        continue
    
    weaknesses = {
        'QB': offense.loc[team, 'pass'],
        'WR': offense.loc[team, 'pass'] + 0.01,
        'OL': (offense.loc[team, 'run'] + offense.loc[team, 'pass']) / 2,
        'RB': offense.loc[team, 'run'],
        'CB': -defense.loc[team, 'pass'],
        'S': -defense.loc[team, 'pass'] + 0.01,
        'DE': -defense.loc[team, 'pass'] + 0.02,
        'LB': -defense.loc[team, 'run'],
        'DT': -defense.loc[team, 'run'] + 0.01
    }
    
    sorted_needs = sorted(weaknesses, key=weaknesses.get)[:3]
    needs_dict[team] = sorted_needs

os.makedirs('data', exist_ok=True)
df = pd.DataFrame.from_dict(needs_dict, orient='index')
df.to_csv(f'data/{draft_year}_needs.csv', header=False)