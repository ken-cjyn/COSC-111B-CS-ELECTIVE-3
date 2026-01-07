import serial
import time
import os
import threading

PORT = 'COM4' 
BAUD = 9600

def show_instructions():
    os.system('cls' if os.name == 'nt' else 'clear')
    print("=" * 55)
    print(" LAB 6: BIDIRECTIONAL USING PYTHON AND ARDUINO ".center(55, "#"))
    print("-" * 55)
    print(" INSTRUCTIONS:")
    print(" 1. Press hardware buttons to toggle LEDs.")
    print(" 2. Enter 1/R, 2/G, or 3/B to toggle LEDs.")
    print(" 3. Enter 'EXIT' to turn off LEDs and quit.")
    print("-" * 55)
    print(" RESTRICTION: Single character only.")
    print("=" * 55)

def listen_to_arduino(ser):
    while ser.is_open:
        if ser.in_waiting > 0:
            try:
                btn_signal = ser.readline().decode('utf-8').strip().upper()
                if btn_signal == 'R':
                    ser.write(b'1')
                    print("\nEVENT: RED TOGGLE\ncommand: ", end="", flush=True)
                elif btn_signal == 'G':
                    ser.write(b'2')
                    print("\nEVENT: GREEN TOGGLE\ncommand: ", end="", flush=True)
                elif btn_signal == 'B':
                    ser.write(b'3')
                    print("\nEVENT: BLUE TOGGLE\ncommand: ", end="", flush=True)
            except:
                pass
        time.sleep(0.01)

arduino = None

try:
    arduino = serial.Serial(PORT, BAUD, timeout=0.1)
    time.sleep(2)
    show_instructions()

    listener_thread = threading.Thread(target=listen_to_arduino, args=(arduino,), daemon=True)
    listener_thread.start()

    while True:
        user_input = input("command: ").strip().upper()

        if user_input == "EXIT":
            arduino.write(b'0') 
            print("Turning off LEDs and exiting...")
            time.sleep(1)
            break
        
        if not user_input:
            continue
            
        if len(user_input) == 1:
            if user_input in ['1', 'R']:
                arduino.write(b'1')
                print("EVENT: RED TOGGLE")
            elif user_input in ['2', 'G']:
                arduino.write(b'2')
                print("EVENT: GREEN TOGGLE")
            elif user_input in ['3', 'B']:
                arduino.write(b'3')
                print("EVENT: BLUE TOGGLE")
            else:
                print("Invalid command.")
        else:
            print("ERROR: Single input only at a time!")

except Exception as e:
    print(f"\n[!] Error: {e}")
finally:
    if arduino and arduino.is_open:
        arduino.close()