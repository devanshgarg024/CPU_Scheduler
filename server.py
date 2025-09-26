from flask import Flask, request, jsonify, send_from_directory
import subprocess
import os
import json
import time

app = Flask(__name__, static_folder=None) # Disable default static folder

PROCESS_FILE = os.path.join('resources', 'process.json')

def read_processes():
    with open(PROCESS_FILE, 'r') as f:
        return json.load(f)

def write_processes(processes):
    with open(PROCESS_FILE, 'w') as f:
        json.dump(processes, f, indent=4)

# Route to serve the main HTML page
@app.route('/')
def index():
    return send_from_directory('.', 'index.html')

# API endpoint to get the initial list of processes
@app.route('/get-processes', methods=['GET'])
def get_processes():
    try:
        processes = read_processes() if os.path.exists(PROCESS_FILE) else []
        return jsonify(processes)
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# API endpoint to add a new process
@app.route('/processes', methods=['POST'])
def add_process():
    try:
        new_proc = request.get_json()
        processes = read_processes()
        if any(p['pid'] == new_proc['pid'] for p in processes):
            return jsonify({"error": "Process with this PID already exists"}), 409
        # Add default values for fields not in the form
        new_proc.update({"vruntime": 0, "processState": {"counter": 100}})
        processes.append(new_proc)
        write_processes(processes)
        return jsonify(new_proc), 201
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# API endpoint to update an existing process
@app.route('/processes/<int:pid>', methods=['PUT'])
def update_process(pid):
    try:
        updated_proc_data = request.get_json()
        processes = read_processes()
        proc_to_update = next((p for p in processes if p['pid'] == pid), None)
        if not proc_to_update:
            return jsonify({"error": "Process not found"}), 404
        proc_to_update.update(updated_proc_data)
        write_processes(processes)
        return jsonify(proc_to_update)
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# API endpoint to delete a process
@app.route('/processes/<int:pid>', methods=['DELETE'])
def delete_process(pid):
    try:
        processes = read_processes()
        original_length = len(processes)
        processes = [p for p in processes if p['pid'] != pid]
        if len(processes) == original_length:
            return jsonify({"error": "Process not found"}), 404
        write_processes(processes)
        return jsonify({"success": True})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# API endpoint to run the simulation
@app.route('/run-simulation', methods=['POST'])
def run_simulation():
    data = request.get_json()
    algorithm = data.get('algorithm')

    if not algorithm:
        return jsonify({"error": "Algorithm not specified"}), 400

    try:
        # --- Step 1: Run the C++ scheduler ---
        # Assumes the executable is in the 'build' directory, as created by build.sh
        cpp_executable = os.path.join('build', 'cpu_scheduler')
        subprocess.run([cpp_executable, algorithm], check=True, capture_output=True, text=True)

        # --- Step 2: Run the Python plotting script ---
        subprocess.run(['python', 'plot.py'], check=True, capture_output=True, text=True)

        # --- Step 3: Read process data ---
        processes = read_processes() if os.path.exists(PROCESS_FILE) else []

        # --- Step 4: Return the path to the generated image and process data ---
        image_path = f'/process_schedule_dark.png?v={time.time()}' # The browser will fetch this from the root
        return jsonify({"image_path": image_path, "processes": processes})

    except subprocess.CalledProcessError as e:
        return jsonify({"error": "Failed to run simulation", "details": e.stderr}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# API endpoint to show the plot in a pop-up window
@app.route('/show-plot', methods=['POST'])
def show_plot():
    try:
        # Run the plotting script with the '--show' argument
        # This will use the default interactive backend and call plt.show()
        subprocess.run(['python', 'plot.py', '--show'], check=True, capture_output=True, text=True)
        return jsonify({"success": True, "message": "Plot window should be visible."})
    except subprocess.CalledProcessError as e:
        return jsonify({"error": "Failed to show plot", "details": e.stderr}), 500
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# Route to serve static files like the plot image
@app.route('/<path:filename>')
def serve_static(filename):
    return send_from_directory('.', filename)

if __name__ == '__main__':
    port = int(os.environ.get('PORT', 5000))
    app.run(debug=False, host='0.0.0.0', port=port)
