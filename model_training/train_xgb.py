import xgboost as xgb
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
import pandas as pd
from feature_engineering import add_time_features, add_lagged_features

# Load and parse data, assuming 'timestamp' column exists
data = pd.read_csv("data_collection/simulated_data.csv", parse_dates=['timestamp'])

# Add time-based cyclic features for day of week and hour of day
data = add_time_features(data)

# Add lagged features for each environmental parameter (e.g., last 5 readings)
data = add_lagged_features(data, lag_steps=5)

# Drop any rows with NaN values due to lagging
data.dropna(inplace=True)

# Define input features (X) and target variable (y)
# Here, we're predicting 'oxygen' based on its own past values and those of other parameters
X = data.drop(columns=['oxygen', 'pressure', 'humidity', 'temperature'])
y = data['oxygen']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Initialize and train XGBoost model
model = xgb.XGBRegressor()
model.fit(X_train, y_train)

# Evaluate the model
y_pred = model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
print(f"Mean Squared Error: {mse}")

