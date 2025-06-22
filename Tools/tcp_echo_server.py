# Copyright : 2025 Kei.K
# SPDX-License-Identifier: BSD-3-Clause
import socket

def main():
    host = "192.168.137.1"   # The address on which the server will bind. Use "" to bind to all interfaces.
    port = 5000         # The port number on which the server will listen.

    # Create a socket using IPv4 (AF_INET) and TCP (SOCK_STREAM)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()  # Start listening for incoming connections.
        print(f"Server is listening on {host}:{port}")
        
        while True:
            # Accept a connection from a client.
            conn, addr = s.accept()
            print("Connected by", addr)
            with conn:
                while True:
                    # Receive data from the client (up to 1500 bytes)
                    data = conn.recv(1500)
                    if not data:
                        # If no data is received, the client has closed the connection.
                        break
                    print("Received:", data.decode())
                    # Echo the received data back to the client.
                    conn.sendall(data)
            print("Connection closed with", addr)

if __name__ == "__main__":
    main()
