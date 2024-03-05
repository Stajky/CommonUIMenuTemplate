# CommonUIMenuTemplate
This project is a research project that explores the experimental CommonUI plugin from Unreal Engine. It should work as an example/template for future implementations.

This project also worked as an "How would I implement UI?" learning resource. Because the best way to learn is to just code

## Road map:
- [x] Main menu
- [x] Credits
- [x] Loading screen
- [x] Save and load system
- [x] Load and save UI
- [x] Player HUD
- [x] Mock/Cheat GAS-like communication for Widget Controllers
- [x] Pause menu
- [x] Settings
- [x] Beautify (well at least make passable :D)
- [x] Write summary about CommonUI

## Setup
To start this project I recommend building from source:
1. Get the project files to your machine (git clone, simple zip file download, ...)
2. Right click on the UE project file and select generate Visual Studio Project files
3. Open it in VS and Build the solution


> [!IMPORTANT]
> This project uses Seamless Travel so for full experience start it in Standalone. If you play in PIE it will work the same only you will not see the loading screens.



## Controls  
**PC:**  
(shift + =) => Cheat Menu  
(W,A,S,D) => movement controls  
(Mouse) => look around  
(Mouse Click) => menu selection  
(Tab) => Pause Menu

**Controller:**  
(Controller A,B,X,Y) => menu selection  
(Left Joystick) => movement  
(Right Joystick) => look around  
(Start) => Pause Menu  


## System overview
### General Input
Main strength works with controller but makes integration with enhanced input somewhat difficult because it uses table system when UE5 is all about enhanced input. CommonUI also works for other Input systems which is desired. The qist of how CommonUI achieve this is that every input is mapped to a virtual mouse and this mouse is used to "click on stuff"
What I would like is something similar by default in unreal engine as the end layer that actually clicks and navigates on stuff. Why general, well because you mouse gets high-jacked by CommonUI and gamepad bottom button is literally marked to mouse click and now you cant use gamepad bottom button in enhanced UI (a small price but annoying).


### The layer/stack system
CommonUI uses a stack system to keep track what is on the screen on which layer. I use 4 layers Game, GameMenu, Menu, Modal basically defines a ZOrder AKA what is rendered on top of what. To "get stuff on screen" you use push widget to layer function, which you can call from anywhere all you need to specify the widget you want to display and this function will add it to screen and activate the widget. For removing stuff from screen you use PopFromScreen (this will also call deactivate widget). I realy like this way of controlling what is on screen using just two function also its great for menu navigation when you want to go back you just call pop from screen. Another great thing is that CommonUI is caching previous widgets and you dont lose on performance  
One minus that I found which is not a deal-breaker is that each layer can have only one widget at a time and it limits you if you want to show two menus at one time


### GameplayMessageSubsystem (GMS for short):
I heavily used this system for communication between widgets and widget controllers, it gives an easy way for the Publish–subscribe pattern to be implemented in Widgets. In GMS to define the data we want to send we create Messages. Messages are structs where we define the data we want to send. A great strength of this is that we can easily define and variables just create a string for them.
Another concept here is channel, this represents an ID based on which we decide where the message should go. The channel is a GameplayTag.  
I like this system a lot and I think its one of the best things that I learned about when exploring CommonUI, I recommend using it and not only for UI


### Buttons
CommonUI uses CommonButtonBase which is sadly poorly documented and one has to read the source code to see what is going on. This class has a lot to offer and its pointless to go over all the details, I will share the main ones that I deem interesting.  
First we have the UCommonActionWidget variable that shows an icon based on what is our input (the A for controller in this project case). This means two things the first one is that CommonButtonBase automatically listened for input change and based on it switches icons for another and second that there is a systems for defining what icon should be called. The automatic system is automatic so we don't need to concern ourselves with it but its good to know. As for "What icon should we show?" we set a an input action from the data table we defined in CommonUI setup https://docs.unrealengine.com/5.0/en-US/common-ui-quickstart-guide-for-unreal-engine/ based on it CommonUI will determine what icon it should use from the Data Binding (see Chapter 4 in the link).


### Material
Material or rather a Shader is one of the most powerful tool we have when it comes to UI. Here I used it to animate onhover and selected effects using SDF. I used UIMaterialLab project where you basically have components implemented in materials and transform them little bit to get desired result. For setting the parameters on could you the SetScalarParameterValue functions and I did use them of course but what I found better way. I used the UI animation tool to set these parameters and just played animation whenever I needed (mostly on hover).

I also used material from Lyra for progress bar which I for the slider editor. I used it instead of base Progress bar because you have more options in the Material in this instance a way to indicate a default value with a lighter bar.


### Slate
I use slate loading screen and for Editor slot.  
I am of the belief that one should not reinvent the wheel and so I chose the most logical approach and only add logic on top of existing one. Or rather I wanted to, but since inheritance is not something you do in slate (well you do but there is sometimes magic preventing you from actually calling construct method even though you know it exist) I had to recreate a SliderEditor by copy pasting most of the code in Slider class and adding logic on top of it.  
I also used the trick that I learned by reading Slate classes to use inheritance but it only works if you use it only one level down. The parent class has to have SLATE_DECLARE_WIDGET(SSlider, SLeafWidget) => this macro will do some magic and will make your Construct method available in the children. This is as far as I got and suffice to say I just went with the copy paste route to save me some time and sanity.

#### Why did I even need to touch slate?
well for the loading screen since the loading is happening so early in the project loading process the UMG module is not loaded yet so slate is the only option we have.   
And for the Editor slot its because Slate handles focus and I needed to expose functions that handle focus that are normally not exposed, and you can expose them only by using slate.

I should also mention that you need to create combo SWidget + UWidget, where SWidget is sort of the backend Slate logic and UWidget works as an API for Unreal Engine (it holds a pointer to SWidget so that GC won't clear it).

For better and more info look at https://github.com/YawLighthouse/UMG-Slate-Compendium and read the engine code for Slate classes this will give you even better idea, but still its trial and error when it comes to these things since documentation is so poor.


### Widget Communication
for widget communication I use the basic MVC pattern where a Widget Controller is created as an middle-men that sends data to Widgets via GMS. The widgets live on HUD. HUD gives as an easy access to all of them and works as the center for all communication for the widget controllers but since image can say a thousand words here is a diagram:

![Diagram of Widget Communication](Docs/Image/WidgetCommunication.png?raw=true "Widget Communication")

## Main UI parts:
### Credits
For credits I used dynamic approach where one just define a list of names and categories and you are set. But using this I noticed a weird artefact when animating the credits going up sometimes they lagged a little bit and because of this I would use an external tool mp4 tool where I would create a video to fix that.  
The system behind the animation is simple scroll box with animated scroll bar going up. For the initial and end empty space I used two spacer. There is also an option to skip using the skip button that uses by holding enter.


### Loading screen
For loading screen I used the unreal media player class, and was inspired by the RPG Project for UE peeps. Thanks to this you can specify what movies to play in first loading screen. In this case I added the an unreal logo loading screen. The media player runs on different thread than the main game so its doesn't take that much resources and is a true loading screen.  
To show other loading screens you call a BP function show loading screen and all you need to do is specify parameters for it, such as the minimal time the loading screen should be on screen.  
Also it should be noted that because how the media player is setup, one needs to create a Slate Widget. This is due to the fact that this is called very early in the loading phase and UMG is not yet ready also its called in a different module and you have to specify that the module is loaded in preload phase.


### Save and load
For save and load system I used SPUD open source library, I use it to minimal capacity but its a fully fleshed out save system that I recommend using instead of the base one from unreal engine. I wont go into details here because more can be found on https://github.com/sinbad/SPUD where its described better than I could.  
For the UI I used an dynamic approach with where I load the save file meta data from SPUD and each entry I will add to a scrollbox. Thanks to SPUD I dont need to implement save screenshot logic, save timestamp, etc. I can just access it and display it with SaveSlot widget


### Player Overlay
Player hud is a simple Mock data based widget that uses all the already mention principals so I wont go into too much detail here. The idea here was to create a widget that is designed to handle GAS like input but in doing so I made it generic enough that it doesnt really depend on anything you just need to send the right message to the right listener and data will be displayed.


### Cheat Menu
Cheat menu is a simple widget that is used to demonstrate changes in the mock GAS like data and implements how to send data from UI back to backend. There In Cheat Menu Widget Controller I also created and enhanced input listener that will onActive/Deactivate add/remove IMC essentially handling what input should we react to based on UI. In the Cheat menu it will activate all the spells. It worked as an experiment do it then see how you like it. I am still undecided if I like it here or not, well future me will tell me this tho.  
PS: Cheat menu uses buttons to set values and is not designed to work with controller as well, you can treat it as an debug tool and one does run unreal on a console.


### Settings
Settings menu is probably the most advanced out of all the menus. It works as an widget switcher with extra logic for widget activation/deactivation and handling communication to Setting description.
The switcher/activator part is implemented in Tab Panel a panel that contain in this case three buttons for Graphics, Audio and Controls. One has to register these buttons in the main setting widget and also give reference to the widget they should be showing/activating. One can navigate the Tab Panel widget by button click (RB, LB on controller).
For the setting editors themselves there are two main ones SettingsEditorDiscrete and SettingsEditorSlider using these to you will most cases and for my mock settings data they are enough. Both use and abuse the materials to indicate the value of the setting and use the slate widgets for controller (better widget navigation).
The setting description window works as a simple panel with a rich block. And on hover each setting will send a rich text string to the description where you display the desired data.
PS: The setting themself have no backend just UI and hence will not be save and will not change any settings



