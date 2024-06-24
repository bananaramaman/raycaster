//////////////////////////Texture and map creation/////////////////////////

to create a map from an image.
1. create a 16x16 pixel image (suit to size of array 8x8, 32x32, 64x64 etc.)
2. save as .BMP 24bit colors
3. import .bmp into gimp & export as .ppm file with ASCII values (important!!!)
4. Using Notepad++ create a macro to remove 2 lines while keeping the value representing the texture.
 (eg. 	255 >>delete
	255 >>delete
	12  >>keep
 )
5. This can be done by moving the cursor to the start of the line and pressing CRTL + L
6. once the extra values are removed, use find & replace to add a comma to the end of each line This can be defined as (find: $ replace: ,)
7. Finally add int array[]={ enclose values };

creating texture maps is exactly the same process, only once finished step 3 proceed to step 6.