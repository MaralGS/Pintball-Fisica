# GetIgnore
# Pintball
This pintball is a original game maked for Pol Maresch and Alex garcia

Source Code: https://github.com/MaralGS/Pintball-Fisica

## Developers:

-Alex Garcia Selma ([Github])(https://github.com/MaralGS))
-Pol Maresch Marxuach ([Github])(https://github.com/rayolop20))

## Controls:
 -Left Key: Move Left Stick
 -Right key: Move Right Stick
 -Down Key: Move Kicker Ball
 -F1: You see all shapes from the game
 -Left Mouse Click: You can move the ball on the map
 -1 Key: Teleport ball to your mouse position
 -R key: Restart game (Restart Lives, Ball position and scores)
 -Esc Key: Close game

## Features:
 -If you hit all Ball Bumpers (static obstacle) you get 1 live extra
 -If you hit Ball Bumpers or Bumpers the ball bounces
 -When trow one ball, is created a wall by one sensor on the exit ball,
  that makes you unable to return the ball to the starting position inadvertently.
 -Added original sounds
 -Score, Last Score and Highest score
 -Time step

##How we maked the game:
 We started making the map and adding walls and ball position, when we had that, then we started to make joins, the sticks and push ball joins, and there we
 had the firts problems, first of all the sticks colide with the walls and get stucked with them, we solve that separating sticks from rotation position.
 With push ball we had another problem, that somtimes stoped and didn't work, for solve that we needed to reduce and move the push walls and position, 
 because we think that the walls of push ball and map walls was colision with them and this stop the joint.

 Then we maked the win and score sensors, that we had no real big problems, after this we maked the bumpers, and we had problems with the velocity, 
 position and angle thats trows the ball, we solve that reducing the power that trows the ball, reducing the mesures of colder and makinh a new variable in
 box that this alowed rotate the bar.

 After this we make the First and End screens and lives and score, we didn't have problems with that. After do that we see that we had bullet frame,
 solve that we using the theory learned in class.

 Then we put it the sprites in the ball and sticks and souns, on the images we only had problems with the the image mesure,
 but with audios, we had problems because sometimes that didn't work or the audio sound was elevated, we solve that searching and converting mp3 audios
 to wav.

 And finaly we maked the frame-time that the only problems that we had, was only how to do that, and searching information and examples we maked.

   

	 
	