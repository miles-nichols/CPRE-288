# import tkinter as tk

# # Function to be executed when button is clicked
# def on_button_click():
#     label.config(text="Hello, World!")

# # Create the main window
# window = tk.Tk()
# window.title("Simple Tkinter GUI")

# # Create a label widget
# label = tk.Label(window, text="Press the button")
# label.pack(pady=20)

# # Create a button widget
# button = tk.Button(window, text="Click Me", command=on_button_click)
# button.pack(pady=20)

# # Start the Tkinter event loop
# window.mainloop()

import tkinter as tk

# Function to be executed when button is clicked
def on_button_click():
    name = name_entry.get()  # Get the text from the Entry widget
    if name:
        greeting = f"Hello, {name}!"
    else:
        greeting = "Hello, World!"
    label.config(text=greeting)  # Update the label text
# Create the main window
window = tk.Tk()
window.title("Personalized Greeting GUI")
# Create a label widget
label = tk.Label(window, text="Enter your name and press the button")
label.pack(pady=20)
# Create an Entry widget for user input
name_entry = tk.Entry(window)
name_entry.pack(pady=10)
# Create a button widget
button = tk.Button(window, text="Greet Me", command=on_button_click)
button.pack(pady=20)
# Start the Tkinter event loop
window.mainloop()

