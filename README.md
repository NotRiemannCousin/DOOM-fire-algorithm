# DOOM-fire-algorithm
Implementation of the DOOM game fire algorithm (without the wind) in the __C++ SFML library__

<iframe src="https://www.youtube.com/embed/VNcEp07wUAY">
</iframe>

*Demonstration of the algorithm*

___

## "How do it works?"
This algorithm is very simple. Basically, it consists of an two-dimensional array of "RectangleShape"s that contains all the "pixels" (lets call it <span style="color:blue">grid</span>) and another two-dimensional array of "int"s with the same size that stores the fire intensity of each of these "pixels" (lets call it <span style="color:red">fire</span> because it does all the magic). For each fire intensity value, a corresponding color is displayed.

Note: The <span style="color:blue">grid</span> and the <span style="color:red">fire</span> are Strictly connected, so, for each position on the <span style="color:blue">grid</span> there is a corresponding one on the <span style="color:red">fire</span>.

The maximum intensity of the fire is 36, so we must also have a linear array of 37 positions (from 0, where the fire will be completely off, to 36, maximum) storing the colors of the fire.

~~~c++
Int gridSizeY = 40, gridSizeX = 40;

	RectangleShape grid [gridSizeX] [gridSizeY]; // the grid
	int fire [gridSizeX] [gridSizeY]; // the int array

sf::Color colorArray [37] = {
		sf::Color(7, 7, 7), sf::Color(31, 7, 7), sf::Color(47, 15, 7),
		sf::Color(71, 15, 7), sf::Color(87, 23, 7), sf::Color(103, 31, 7),
		sf::Color(119, 31, 7), sf::Color(143, 39, 7), sf::Color(159, 47, 7),
		sf::Color(175, 63, 7), sf::Color(191, 71, 7), sf::Color(199, 71, 7),
		sf::Color(223, 79, 7), sf::Color(223, 87, 7), sf::Color(223, 87, 7),
		sf::Color(215, 95, 7), sf::Color(215, 95, 7), sf::Color(215, 103, 15),
		sf::Color(207, 111, 15), sf::Color(207, 119, 15), sf::Color(207, 127, 15),
		sf::Color(207, 135, 23), sf::Color(199, 135, 23), sf::Color(199, 143, 23),
		sf::Color(199, 151, 31), sf::Color(191, 159, 31), sf::Color(191, 159, 31),
		sf::Color(191, 167, 39), sf::Color(191, 167, 39), sf::Color(191, 175, 47),
		sf::Color(183, 175, 47), sf::Color(183, 183, 47), sf::Color(183, 183, 55),
		sf::Color(207, 207, 111), sf::Color(223, 223, 159), sf::Color(239, 239, 199),
		sf::Color(255, 255, 255)}; //the colors we are going to use


~~~
*The code*

![grid](https://media.discordapp.net/attachments/798356705129136151/924198465788084264/311_Sem_Titulo_20211224213141.png)
*The formatted grid*

![fire](https://media.discordapp.net/attachments/798356705129136151/924208788528037898/313_Sem_Titulo_20211225045428.png)
*Visual representation of the <span style="color:red">fire</span> matrix*

![colorArray](https://media.discordapp.net/attachments/798356705129136151/924078743847305277/1_39evHRnjVN_D78B09Tzf7A.png)
*Representation of the color array, from 0 to 36*

___

Now, we have to set the maximum intensity of the fire for each <span style="color:red">fire</span> of the bottom line and paint the corresponding shapes on the <span style="color:blue">grid</span> (with the <span style="color:green">colorArray</span>). The other positions of the <span style="color:red">fire</span> must be equal to 0.

~~~C++
for (int j = 0; j < gridSizeY; j++)
{
   	for (int i = 0; i < gridSizeX; i++)
	{
       if( i = gridSizeX - 1) // I have positioned the grid matrix so that the bottom row is the last
       {
	    		fire [i] [j] = fireIntesive;
       }else
       {
          fire [i] [j] = 0;
       }
       grid[i] [j].setFillColor(colorArray [ fire [i] [j] ]);
  	}
}
~~~
![fire_2](https://media.discordapp.net/attachments/798356705129136151/924208788314144819/312_Sem_Titulo_20211225045520.png)
![grid_2](https://media.discordapp.net/attachments/798356705129136151/924208788838445067/314_Sem_Titulo_20211225045342.png)

___

That bottom line is the source of fire. It is who will trigger the final effect.

All this was running before the "while(window.isOpen())", we was just "fixing the terrain". Now we will create the part that is realy cool and blow mind, the algorithm.

First, let's take the first grid from the top (in this case, the <span style="color:green">grid [1] [1]</span>) and look at the grid below it (in this case, the <span style="color:green">grid [1] [2]</span>). For now, let's leave the <span style="color:red">fire</span> of the <span style="color:green">grid [1] [1]</span> (<span style="color:red">fire [1] [1]</span>) equal to <span style="color:red">fire</span> of the <span style="color:green">grid [1] [2]</span>(<span style="color:red">fire [1] [2]</span>) minus 1. After that, paint the <span style="color:green">grid [1] [1]</span> with the color of <span style="color:red">fire [1] [1]</span> in the <span style="color:green">colorArray</span>, as we did before. Generalize this to all grids excluding those from the source, as there are no other grids below them, and even if there were, this would cause the fire to suddenly go out. As negative numbers will only hinder us here, make sure that whenever a <span style="color:red">fire [j] [i]</span> become negative, it will be equal 0.

Note: If you do it starting at the bottom, the result will not be as expected. This process has to start at the top.

~~~C++
for (int j = 0; j < gridSizeX; j++)
		{
			for (int i = 0; i < gridSizeY - 1; i++)
			{
				int decay = 1;	
				fire[j] [i] = fire[j] [i + 1] - decay;
        if(fire[j] [i] < 0)
           fire[j] [i] = 0;
					
				grid[j] [i].setFillColor(colorArray [ fire [j] [i] ]);
  	}
}
~~~
![fire_3](https://media.discordapp.net/attachments/798356705129136151/924231909670809600/315_Sem_Titulo_20211225062200.png)
![grid_3](https://media.discordapp.net/attachments/798356705129136151/924231910002163792/316_Sem_Titulo_20211225062722.png)
*It's taking shape*
___

Now we just need to set the "decay" how a random number (preferably between 0 and 3) and... "That's it?" Yes, finishing that the base algorithm is ready.
~~~C++
for (int j = 0; j < gridSizeX; j++)
		{
			for (int i = 0; i < gridSizeY - 1; i++)
			{
				int decay = rand()%4;
				fire[j] [i] = fire[j] [i + 1] - decay;
        if(fire[j] [i] < 0)
           fire[j] [i] = 0;
					
				grid[j] [i].setFillColor(colorArray [ fire [j] [i] ]);
  	}
}
~~~

![grid_4](https://media.discordapp.net/attachments/798356705129136151/924245806343680010/317_Sem_Titulo_20211225072003.png)
*Looks good*
![fire_4](https://media.discordapp.net/attachments/798356705129136151/924245806578552862/317_Sem_Titulo2_20211225072229.png)
