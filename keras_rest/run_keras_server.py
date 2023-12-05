# Import the necessary packages
from keras import models
import numpy as np
import flask
import json

# Initialize our Flask application and the Keras model
app = flask.Flask(__name__)
model = None

def load_model():
	# load the pre-trained Keras model (here we are using a model
	# pre-trained on ImageNet and provided by Keras, but you can
	# substitute in your own networks just as easily)
	global model
	model = models.load_model("./models/chessai.keras")

@app.route("/predict", methods=["POST"])
def predict():
	# initialize the data dictionary that will be returned from the
	# view
	data = {"success": False}
	
	print("Received request")

	# ensure an image was properly uploaded to our endpoint
	if flask.request.method == "POST":
		if flask.request.form.get("board"):
			data["success"] = True
			board_json = flask.request.form.get("board")
			board_flattened = np.asarray(json.loads(board_json))
			board = np.reshape(board_flattened, (1, 8, 8, 12))
			data["output"] = model.predict(board).tolist()[0][0]

	return flask.jsonify(data)

# if this is the main thread of execution first load the model and
# then start the server
if __name__ == "__main__":
	print(("* Loading Keras model and Flask starting server..."
		"please wait until server has fully started"))
	load_model()
	app.run(port=10001)
