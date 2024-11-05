import os
import time
import xgboost as xgb
import onnxruntime as ort
from sklearn.metrics import mean_squared_error, r2_score
from prettytable import PrettyTable

def evaluate_model(model_path, X_test, y_test):
    session = ort.InferenceSession(model_path)
    input_name = session.get_inputs()[0].name
    y_pred = [session.run(None, {input_name: X_test[i:i+1].astype(np.float32)})[0][0] for i in range(len(X_test))]
    mse = mean_squared_error(y_test, y_pred)
    r2 = r2_score(y_test, y_pred)
    return mse, r2

def measure_latency(model_path, X_test):
    session = ort.InferenceSession(model_path)
    input_name = session.get_inputs()[0].name
    start_time = time.time()
    for i in range(len(X_test)):
        session.run(None, {input_name: X_test[i:i+1].astype(np.float32)})
    return (time.time() - start_time) / len(X_test) * 1000

def calculate_flops(model):
    depth = model.get_params()['max_depth']
    num_trees = model.get_booster().trees_to_dataframe().shape[0]
    return num_trees * (2 ** depth)

table = PrettyTable(["Model", "Size (MB)", "Latency (ms)", "FLOPs", "MSE", "R2"])
