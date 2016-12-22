import socket

# Set broadcast port to match the code running on Wemos
broadcast_port = 12345

# Initialize UDP socket listener
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# Listen on all network devices, on the selected port
s.bind(('0.0.0.0', broadcast_port))


while True:
    # Message length is 19 characters, so receive them
    message, sender = s.recvfrom(68)
    # Print out the message
    print(message)
