from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
@app.route("/home")

def home():
  return render_template("index.html")

@app.rout("/result")
def result():
  output = request.form.to_dict()
if __name__ == '__main__':
  app.run(debug=True, host="10.0.4.40", port=8000)
