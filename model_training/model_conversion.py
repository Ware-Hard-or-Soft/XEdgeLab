import onnx
import tensorflow as tf
from onnx_tf.backend import prepare
import onnxmltools

onnx_model = onnxmltools.convert_xgboost(model, target_opset=10)
tf_rep = prepare(onnx_model)
tf_rep.export_graph("tf_model")

converter = tf.lite.TFLiteConverter.from_saved_model("tf_model")
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()

with open("model_training/XEdgeLab_tflite_model.tflite", "wb") as f:
    f.write(tflite_model)
