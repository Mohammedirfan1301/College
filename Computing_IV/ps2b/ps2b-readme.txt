Name: Jason Downing

Comments:

My program fully works. I can successfully encrypt an image, as well as decrypt it given
the same seed and tap position.

For the screenshots, I used the following commands:

Encoding
./PhotoMagic dogecar.png output-file.png 0011001100000 8

Decoding
./PhotoMagic output-file.png dogecar.png 0011001100000 8

I used two windows for my program - one shows the input image, the other shows the output image.

It also seems to ignore transparent parts of images. I'm not entirely sure why, but it does randomize
the parts of the image which are not transparent. The program works fine