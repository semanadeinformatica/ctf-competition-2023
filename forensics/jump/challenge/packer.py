from PIL import Image
import tarfile
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

def add_payload_to_image(image, payload):
    with open(payload, "rb") as f:
        payload = f.read()
    
    with open(image, "ab") as f:
        f.write(payload)


frames = []
with Image.open("jump.gif") as img:
    for frame_index in range(img.n_frames):
        img.seek(frame_index)
        frames.append(img.copy())

with open("keypair.pem") as f:
    keypair = f.read()
    

img_key_path = "jump_with_key.gif"
with Image.new(frames[0].mode, frames[0].size) as img_key:
    img_key.save(img_key_path, save_all=True, loop=0, append_images=frames, optimize=False, comment=keypair)

with open("message.txt") as msg_file:
    message = msg_file.read()

keypair = RSA.import_key(keypair)

pub_key = PKCS1_OAEP.new(keypair)
encrypted_message = pub_key.encrypt(bytes(message, 'utf-8'))

# Open and truncate or create new file
with open("message.txt.enc", "wb") as msg_file:
    msg_file.write(encrypted_message)

# Tar and gzip the encrypted message
with tarfile.open("message.txt.enc.tar.gz", "w:gz") as tar:
    tar.add("message.txt.enc")
    
add_payload_to_image(img_key_path, "message.txt.enc.tar.gz")

# Remove files
import os
os.remove("message.txt.enc")
os.remove("message.txt.enc.tar.gz")
