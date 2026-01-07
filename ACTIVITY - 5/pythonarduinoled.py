
import serial
import time
import os
import sys

SERIAL_PORT = 'COM4'  
BAUD_RATE = 9600


def clear_screen():
    """Clears the console screen."""
    os.system('cls' if os.name == 'nt' else 'clear')


def print_menu():
    """Displays the menu choices."""
    print("=" * 40)
    print("  Arduino 3-LED Serial Controller")
    print("=" * 40)
    print("[R] Red ON/OFF")
    print("[G] Green ON/OFF")
    print("[B] Blue ON/OFF")
    print("[A] All ON")
    print("[O] All OFF")
    print("[X] Exit")
    print("=" * 40)


def send_and_receive(ser, command):
    """Sends a command to the Arduino and prints the response."""
    
    command = command.upper()

    if not command:
        return

    print(f"\n[PC] Sending: {command}")

    try:
        if ser.is_open:
            ser.reset_input_buffer()     
            ser.write(command.encode()) 
            ser.flush()
            print("[PC] Command sent.")

            time.sleep(0.5)

            
            response_received = False
            timeout_counter = 0
            max_timeout = 10

            while timeout_counter < max_timeout:
                if ser.in_waiting > 0:
                    line = ser.readline().decode(errors='ignore').strip()
                    if line:
                        print(f"[MCU] {line}")
                        response_received = True
                    time.sleep(0.05)
                else:
                    time.sleep(0.1)
                    timeout_counter += 1

                if response_received and ser.in_waiting == 0:
                    break

            if not response_received:
                print("[WARNING] No response from Arduino.")

    except Exception as e:
        print(f"[ERROR] Serial communication error: {e}")


def open_serial_port():
    """Open serial port and return the serial connection."""
    try:
        print(f"Connecting to {SERIAL_PORT}...")
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=2)

        print("Waiting for Arduino to initialize...")
        time.sleep(3)

        print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.\n")

        ser.reset_input_buffer()

        # Read greeting from Arduino if present
        time.sleep(0.5)
        while ser.in_waiting > 0:
            msg = ser.readline().decode(errors='ignore').strip()
            if msg:
                print(f"[MCU] {msg}")
            time.sleep(0.1)

        return ser

    except serial.SerialException as e:
        print(f"\nERROR: Could not open {SERIAL_PORT}")
        print(f"Details: {e}\n")
        print("Troubleshooting:")
        print("- Check Arduino is connected via USB")
        print("- Verify COM port in Device Manager (Windows)")
        print("- Close Arduino IDE Serial Monitor")
        print("- Update SERIAL_PORT in script")
        return None
    except Exception as e:
        print(f"ERROR: {e}")
        return None


def main():
    """Main application loop."""
    print("=" * 50)
    print("Arduino 3-LED Serial Controller - Python Client")
    print("=" * 50)
    print()
    
    ser = open_serial_port()
    
    if ser is None:
        print("\nCannot continue—no Arduino connected.")
        input("Press Enter to exit...")
        sys.exit(1)

    try:
        while True:
            clear_screen()
            print_menu()
            print(f"\n[INFO] Connected to {SERIAL_PORT}")

            choice = input("\nEnter command: ").strip().upper()

            if not choice:
                continue

            if choice == "X":
                clear_screen()
                print("\nTurning off all LEDs before exit...")
                send_and_receive(ser, 'O')  # Turn off all LEDs
                time.sleep(1)
                print("Exiting program. Goodbye!")
                break
            elif choice in ['R', 'G', 'B', 'A', 'O', 'V']:
                send_and_receive(ser, choice)
                time.sleep(1.5)  # Pause to show response
            else:
                print(f"\nInvalid command '{choice}'. Please use R, G, B, A, O, or X.")
                time.sleep(1.5)  # Pause to show error

    except KeyboardInterrupt:
        print("\n\nProgram interrupted (Ctrl+C)")
    
    finally:
        if ser and ser.is_open:
            ser.close()
            print("Serial connection closed.")
if __name__=="__main__":
    main()


