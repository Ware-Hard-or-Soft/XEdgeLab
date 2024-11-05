import numpy as np
import pandas as pd
#To add cyclic feature for time day (7) and hours (24) to get the time pattern
def add_time_features(df):
    df['day_of_week'] = df['timestamp'].dt.weekday
    df['day_sin'] = np.sin(2 * np.pi * df['day_of_week'] / 7)
    df['day_cos'] = np.cos(2 * np.pi * df['day_of_week'] / 7)
    df['hour'] = df['timestamp'].dt.hour
    df['hour_sin'] = np.sin(2 * np.pi * df['hour'] / 24)
    df['hour_cos'] = np.cos(2 * np.pi * df['hour'] / 24)
    return df
#To add temproal feature to include the sequential feature
def add_lagged_features(df, lag_steps=5):
    for i in range(1, lag_steps + 1):
        df[f'Pressure_t-{i}'] = df['pressure'].shift(i)
        df[f'Humidity_t-{i}'] = df['humidity'].shift(i)
        df[f'Oxygen_t-{i}'] = df['oxygen'].shift(i)
        df[f'Temperature_t-{i}'] = df['temperature'].shift(i)
    return df.dropna()
