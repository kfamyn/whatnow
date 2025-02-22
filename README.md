<h1 align=center>whatNow</h1>

<p align=center>A ETU "LETI" C++ course project: cross-platform weather forecast app</p>


https://github.com/kfamyn/whatnow/assets/102179774/90ec8a42-bb98-4026-b139-727a9ccd67af


# Used technologies

- [cURL](https://github.com/curl/curl)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Visual Crossing API](https://www.visualcrossing.com/weather-api)
- [Adobe Photoshop](https://www.adobe.com/products/photoshop.html), [Figma](https://www.figma.com)

# Installation

- [Download for Windows 10 x64](https://drive.google.com/drive/folders/1F6kvKCWHBaDPzXyZoUNG7M9hawGleJDz?usp=sharing)

# User guide

To see forecast for a specific city, enter its' name into ```config.txt``` file. There's no need to enter a full name for big cities (e.g. LA is enough to get 
weather forecast for Los Angeles, California) though if you're not satisfied with the results of a search, try specifying a full address.

To exit the app, click a cross button bottom of a toolbar located to the left.

# Setup for further development

# Extension abilities

### Changing API

The weather API can be changed easily by modifying the **weatherAPI.cpp** file.

To use your **own API key**, generate the key at [Visual Crossing API site](https://www.visualcrossing.com/weather-api) and replace it in 

```67  std::string Weather::request(std::string city)``` method.

To use a **custom API**, you will need to modify the following methods:

```38  std::string Weather::getValue(int day, std::string key)```

```47  std::string Weather::getCurrentConditions(std::string key)```

```56  std::string Weather::getHourlyConditions(int day, int hour, std::string key)```

```67  std::string Weather::request(std::string city)```

to match your JSON (or any other type) file structure.

### Changing the UI design

Source design files can be found [here](https://drive.google.com/drive/folders/1MHNE3X0bIiFR21KZzGY0SP5APGhgvf-c?usp=sharing). All the assets are stored and loaded into ```assets.qrc``` from /assets folder.

### Extending functionality

Following **SOLID** principles, the code is quite easy to extend. All the widget classes are encapsulateed and they are only dependant on ```weatherAPI``` class.

# Main features

## Smooth scroll area

Since the Qt framework doesn't provide with smooth scrolling animation, I had to implement it myself.
The ```SmoothScrollArea``` class can now be used to create smooth scroll areas which consider scroll acceleration.

## Math based widgets

### 'Feels like' widget

```FeelsLikeWidget``` uses somewhat of interval normalization to calculate the temperature gradient position.

### 'Wind' widget

```WindWidget``` uses the equation of a circle to calculate the position of a dot representing wind direction, and then transforms its coordinates from 
the Cartesian coordinate system to Qt's one.

### 'Sun' widget

```SunWidget``` uses the normal distibution equation and interval normalization to calculate the sun position. Therefore, the sun in a widget is always 
representing its' relative position to the horizon line (e.g. if sun sets in 1 hour and there are 12 daylight hours on a given day, the sun in a widget will
be located at 11/12 of the curve part above the horizon line).

## UI design

The UI was fully designed by me, except for using some weather icons (though some of them were also drawn by me).

# Summary

Pros

- OOP, SOLID
- (Therefore) the ease of changing an API, extending and maintaining
- Implementation of unique features
- Pleasing UI

Cons (to get rid of during further development)

- No multithreading
- No optimization for different screen sizes and resolutions
