import tkinter as tk
import socket
import threading

class CybotGui:
    self.root = root
        self.root.title("Cybot Control")

        # Create a frame for the buttons
        self.frame = tk.Frame(self.root)
        self.frame.pack()

        # Movement buttons
        self.forward_button = tk.Button(self.frame, text="Forward", command=self.move_forward)
        self.forward_button.grid(row=0, column=1)

        self.backward_button = tk.Button(self.frame, text="Backward", command=self.move_backward)
        self.backward_button.grid(row=2, column=1)

        self.left_button = tk.Button(self.frame, text="Turn Left", command=self.turn_left)
        self.left_button.grid(row=1, column=0)

        self.right_button = tk.Button(self.frame, text="Turn Right", command=self.turn_right)
        self.right_button.grid(row=1, column=2)

        # Scan button
        self.scan_button = tk.Button(self.frame, text="Scan", command=self.request_scan)
        self.scan_button.grid(row=3, column=1)

        # Label to display the scan results
        self.scan_data_label = tk.Label(self.root, text="Scan Data: None")
        self.scan_data_label.pack()

        # Server details
        self.server_ip = '192.168.1.100'  # Replace with your Cybot's IP
        self.server_port = 12345          # Replace with the correct port

        # Create a socket connection
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def connect_to_server(self):
        try:
            self.sock.connect((self.server_ip, self.server_port))
        except Exception as e:
            print(f"Error connecting to server: {e}")
    
    def send_command(self, command):
        """Send command to the Cybot via socket."""
        try:
            self.sock.sendall(command.encode())
        except Exception as e:
            print(f"Error sending command: {e}")
    
    def receive_data(self):
        """Receive data from the Cybot."""
        try:
            data = self.sock.recv(1024).decode()
            self.update_scan_data(data)
        except Exception as e:
            print(f"Error receiving data: {e}")
    
    def update_scan_data(self, data):
        """Update the GUI with scan data."""
        self.scan_data_label.config(text=f"Scan Data: {data}")

    def move_forward(self):
        self.send_command("MOVE_FORWARD")
        print("Sent MOVE_FORWARD")

    def move_backward(self):
        self.send_command("MOVE_BACKWARD")
        print("Sent MOVE_BACKWARD")

    def turn_left(self):
        self.send_command("TURN_LEFT")
        print("Sent TURN_LEFT")

    def turn_right(self):
        self.send_command("TURN_RIGHT")
        print("Sent TURN_RIGHT")

    def request_scan(self):
        self.send_command("SCAN")
        print("Sent SCAN request")
        # Wait for response in a separate thread
        threading.Thread(target=self.receive_data).start()

    def run(self):
        # Connect to the server (Cybot)
        self.connect_to_server()

        # Start the GUI main loop
        self.root.mainloop()