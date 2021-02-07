# Assignment Repository Skeleton

NOTE!
Our task was to create a 3D game from scratch. I made the rendering engine and the two other group members made the game.  
This rendering engine is VERY flawed. It doesn't draw things by instancing, there is no support for animation, a renderable
object can only have 1 texture, no material customizability. To my defense I was only one person, the time limit was very slim
because we had 2 other courses and we had to learn everything on our own (Our teacher had no programming knowledge.
I have a lot of respect for him, but he shouldn't have held this course. NTNU requires every scientist to hold a course).
of respect for him

Please modify the Readme file to your project specifics, including project name, involved group members (including mail contacts), as well as a version history.

In addition, use this file to describe the project functionality, provide setup instructions, and a brief overview on how to use it.

***Project Name***: Basic Game/Rendering Engine


## Group Members:
* Tobias Ellefsen	(Tobiae)		tobiae@stud.ntnu.no
* Esben Bjarnason	(Esbenlb)		esbenlb@stud.ntnu.no
* Eirik Martin Danielsen	(eirikmda) 	eirikmda@stud.ntnu.no

## Description:
What we've made isn't really a game, but rather a proof of concept. 
At this time we have a first person game where you can walk around on platforms. 
There is collission, point lights and directional light with shadows.	It might not
look like much, but the code is built for expandability.
## Group Allocation
* Esben		Game
* Tobias	Game
* Eirik 	Renderer
## Renderer:
Note. Because Eirik worked on the renderer this section is written by Eirik and he will be referring to himself:

The renderer is completely seperated from the game engine and has to be communicated
with to get anything to the screen. This makes it easy to fix and expand the renderer
with more features in the future.
### Short explanation on the renderer:
Essentiallly all you need to do is tell the renderer to add a model, a texure and a shader and the
renderer will keep track of everything for you. You have to give a handle just like you do to OpenGL
and this handle will become -1 when it's no longer valid. It may or may not change its ID depending on
what is implemented in the future. Note! It is not recommended to store it in a vector (or at least
keep the vector at a consistent size) as when you push back the handle/reference you give the Renderer will
then be invalid. We had quite a problem debugging that in the game engine.

You can add point light, remove point light and edit point light. They don't have shadows.
You can add directional light, move it and remove it. this will cast a shadow.

### What I didn't get to implement in the renderer (due to time):
#### 1.
There are some things that annoy me. The initialization of OpenGl doesn't happen in the renderer, which
means that the renderer isn't completely separated from the actual game. This isn't a hard fix, but it
with a lot of other things) was constantly down prioritized. 
#### 2.
The Renderer isn't a singleton. I would like to make it a singleton, but this also down prioritized.
This is an easy fix.
#### 3.
I would like the renderer to have a default shader so that user of the renderer doesn't have to implement it.
At the time being all the objects are using the same shader and it seems a bit unnecessary to have to add that
shader and make all the game objects use that shader when they want to be drawn. We should absolutely keep the
option to use a different shader, but if you don't care this default shader should be used automatically. 
#### 4.
At the time being the directional shadows is suffering some artifacts. If the light is directed from a low angle you get shadow
acne because a pixel in the shadow map covers a long distance on the surface. The shadows only show when you look at the objects
from a certain angle and you have to be very near to it. I don't know how I will fix this, but i know it occurs when
I render the shadowmapping and use a certain projection. I follow the camera position and keep the same orientation.
This way it will seem like all the objects are in shadow.  
### Game engine:
This part was worked on by Tobias and Esben.

As stated earlier, the game engine communicates with the renderer to do varies tasks throughout the game loop, 
so the essential job of the game engine is give data from its objects for the renderer to use.

Game engine has control of all the objects that gets put into screen by giving them transformation-details, such as position, 
scale and rotation, and also give them an unique id and the type of renderable texture it needs. 
All objects that are intialized are put into a tree where their initial parent are the world object. 
The world object is an abstract object which has zero values. 
The reason behind having a tree is to link each object to each other and the world "screen" they are put into. 
To give an example of similiar environmental aspects objects share in a world could be gravitation, 
and if the velocity for the y-axis got changed for "world" object it would also be changed similiarly for all objects that has world as parent.

Game engine also takes care of the collision of all moving objects. 
By using the collision method of Axis Aligned Bounding Box, it will detect all objects as if they were cubes, 
and negate all velocity that would lead two objects to intersecting. Versioning
	
**Versioning**
