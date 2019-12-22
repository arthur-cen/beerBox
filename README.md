![cover](./images/cover.jpeg)
# Intention
This project establishes an entertaining challenge for the purpose of team building and de-stressing in our community. The motive is to get people to come together to solve this series of challenges, and to introduce more fun into our campus environment. Each challenge corresponds to a hidden box that players must locate and unlock to get to the next stage of the game. The puzzles culminate in a prize... beer!

# Community
Our audience is the community of students at Carnegie Mellon. With the [pervasive culture of academic rigor on campus](https://www.cmu.edu/thinktank/docs/Culture_of_Stress_Think_Tank_Findings.pdf), our hardworking students may not often feel up for attending social events and activities. This can lead to a sense of isolation and [burnout](https://www.buzzfeednews.com/article/annehelenpetersen/millennials-burnout-generation-debt-work?utm_source=dynamic&utm_campaign=bffbbuzzfeedtasty&ref=bffbbuzzfeedtasty&fbclid=IwAR0T_z3NF01HT_8UbZCgM6NVneZrZ9L61ssYZNIUh_y2pm1qksgBCFI9V54). Our project attends to this issue by creating an activity for students based on their needs: the game is overall relatively short and simple, and students can start and stop it at their leisure and availability (assuming there will be restocking of the beers for multiple groups to be able to play). These clever puzzles allow students to think in a creative way. At their completion of the puzzle, they are rewarded with beer and a perfect opportunity to take a break. This should help energize them, invigorate their sense of community, and let them get back to their studies with a small sense of accomplishment.

# Inspiration and Context
[Escape Room](https://theescapegame.com/blog/what-is-an-escape-room/) -- we thought this was a great team-building activity. People of any background can come together to use logic to solve a complicated puzzle. At the end, there is a sense of reward as they get to "escape the room". Our project relates in this way, but it will not require a fixed location.

Video games and board games  -- video games can be a great example of a low-commitment break for busy people. Electronic components can make video games more exciting and stimulating than board games. Board games can be more inclusive since they don't require dexterity for using controllers. For both, there are elements of strategy and teamwork, which make them social activities. Our project is different in that it is more active and gives a tangible reward.

Scavenger hunts -- scavenger hunts allow people to actively search an area and possibly complete a linear series of tasks. Our project is similar but incorporates more difficulty and motivation by implementing riddles and a prize at the end. 

# Process
Starting with a similar concept to a prisoner’s dilemma game, we spent a considerable amount of time figuring out game logistics and balancing the aspects of fun, how challenging it would be, and how well we could implement IoT features. After testing our first prototype and talking to our professor, we found that inventing a captivating game is highly complex and can be unpredictable. Moving forward, we chose a concept structure where players competed against the game and not one another, and this motivated our scavenger hunt game involving riddles, codes, and collaboration within a community.

One concept we worked through during our game design was how the boxes would function to unlock. For example, one iteration of our game had a 9- number keypad where users would enter in a number code. All of these pieces involved setup to connect to the Particle so we reduced the size of the "number pad" and made it binary buttons rather than making each button correspond to a number. We also tested out using potentiometers to dial in number values that could unlock a box. While we made it work, we weighed other options in order to maximize durability and precision of our product. This hardware is sensitive, and if the pieces got shifted or compromised the players would not be able to unlock the box. For future prototypes, we could use another way to enter numbers. 

Another concept we considered was having a linear or parallel structure to the game. Meaning, would opening one riddle box lead to another box? Or, could players unlock boxes in any order and then be able to solve the final puzzle once the others were done? We liked the idea of the former since this meant people would not know what stage of the puzzle they are at, which requires more coordination and effort to determine the scope of the puzzle. 

# Conceptual Design 
Upon coming across the first box (you can't miss it, it's painted like a candy cane), you must solve the riddle inside of the box. This box will be unlocked. When you have entered the correct answer, the light will change to let you know. Then, you must search for the next box. You will know the box is the right one if the green "activated" light is on, and the box is unlocked. Again, repeat, and answer the riddle by dialing the potentiometers correctly. The light will change to let you know your answer is correct, and that the final box, wherever it is, has been unlocked. For the final box, once you find it, there is one final riddle. You can trigger the beer compartment to unlock by speaking the answer to the riddle. If you reach the final box too early, it will be locked and the voice trigger will not work. 

The related context is that the boxes will be stored in dry places on campus. Each box can remotely be re-locked as long as the user closes the lid after using the box. 

# Workflow
1. Open Box 1.
2. Read and solve riddle in Box 1.
3. Enter riddle result into Box 1 input.
4. Box 2 becomes active and thus unlocks.
5. Open Box 2, read and solve riddle.
6. Enter riddle 2 result into Box 2 input.
7. Final Box becomes active and starts to glow.
8. Read and solve riddle on top of BeerBox.
9. Trigger Alexa with riddle answer.
10. Enjoy your beer break!

# Demo
[BeerBox | Designing for the Internet of Things 2019](https://youtu.be/uoTeYMGnfI4)

# Prototype and Implementation

## Riddle Box #1

List of materials 

1. Foamcore
2. Particle Argon#1
3. Neopixel
4. Red and green LEDs
5. 4 buttons

Riddle Box #1 features a game with four led lights, each controlled by one button. The light color will change when the player pushes the button. The next box will open when the player gets the right light pattern. 

![riddle_box1_image](./images/riddle_box1_image.jpeg)
![riddle_box1_diagram](./images/riddle_box1_diagram.jpg)

## Riddle Box #2

List of materials

1. Foamcore
2. Particle Argon#2
3. Servo Motor
4. Neopixel
5. Red and green LEDs
6. 3 potentiometers

Riddle Box #2 features three potentiometers as input that maps from 0 to 9. The red LED light indicates the activation status of the box. The green LED light indicates whether the riddle has been solved. The servo controls the lock of the box.

![riddle_box2_image](./images/riddle_box2_image.jpeg)
![riddle_box2_diagram](./images/riddle_box2_diagram.jpg)

## The Beer Box

List of materials

1. Foamcore
2. Particle Argon#3
3. Servo Motor
4. Neopixel
5. Red and green LEDs
6. Amazon Echo
7. Beer(the trophy)

The Beer Box uses a servo to lock the box. When riddle #2 solved, the Beer Box will be activated. The Neopixel Ring inside the box will glow. The Box is connected with an Amazon Alexa command using IFTTT. And there is an Amazon Echo set onsite. The player can open the box after figuring out the answer and trigger the "unlock" event by saying the answer to Alexa.

![the_beer_box_image](./images/the_beer_box_image.jpeg)
![the_beer_box_diagram](./images/the_beer_box_diagram.jpg)

# Next Steps
One great feature of our project is that new boxes and riddles can be easily introduced to the workflow. We could definitely be able to add more challenging riddle boxes to the game to make sure that it's harder to get the prize. Taking the project forward, we would invest in better hardware; namely, plastic sealed boxes that would not get damaged if they are kept outside or re-used by many players. The potentiometers and buttons could be replaced by more durable pieces. There could also be a sensor utilized to let us know if the box was correctly closed so that we would know if we needed to manually fix one of the riddle boxes as we set the game up for another set of players. From our control panel, we can easily see if the final box gets unlocked, but we could add a sensor to see if the prize gets taken out.

This game idea was well thought out in that it could actually be used on campus, perhaps just indoors, and with us keeping an eye on the boxes and their contents to make sure they aren't being broken by students. Taking it forward, it would truly be a great addition to our community and give students a well-deserved sense of fun.

## Contributers
Anna Gipsov

Arthur Cen

Shrey Agrawal

Austin Van Vark
