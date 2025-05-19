import os
import signal
import subprocess
import time

created = []

def spawn_real_processes():
    count = 0
    while True:
        try:
            proc = subprocess.Popen(["sleep", "1000"])
            created.append(proc.pid)
            count += 1
            if count % 10 == 0:
                print(f"Created {count} processes (PID: {proc.pid})")
        except Exception as e:
            print(f"\nFailed to create process #{count}: {e}")
            break

    print(f"\nTotal processes created: {count}")

def cleanup():
    print(f"\nCleaning up {len(created)} processes...")
    for pid in created:
        try:
            os.kill(pid, signal.SIGTERM)
        except Exception as e:
            print(f"Could not kill PID {pid}: {e}")
    print("Done.")

if __name__ == "__main__":
    try:
        spawn_real_processes()
    except KeyboardInterrupt:
        print("\nInterrupted by user.")
    finally:
        cleanup()
