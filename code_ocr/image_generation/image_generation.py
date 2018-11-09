# -*- coding: utf-8 -*
import random
from PIL import Image, ImageDraw, ImageFont


letterlist='ABCDEFGHIJKLMOPQRSTUVWXYZabcdefghijklmopqrstuvwxyz'
index= random.randint(0,len(letterlist)-1)

##random color for the picture
r=random.randint(0,255)
g=random.randint(0,255)
b=random.randint(0,255)

##random color for the letter
r2=random.randint(0,255)
g2=random.randint(0,255)
b2=random.randint(0,255)
image=Image.new('RGB',(100,100),color=(r,g,b))
##definit la taille et lemplacement de la lettre 
fnt = ImageFont.truetype('arial.tff',15)
## ecrir la lettre sur l'image 
d = ImageDraw.Draw(image)
d.text((80,80),letterlist[index],font=fnt,fill=(r2,g2,b2))

image.save('aleatoireletter.png')

