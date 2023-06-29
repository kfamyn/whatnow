<h1 align=center>whatNow</h1>

<p align=center>Cross-platform weather forecast app. Currently, Windows desktop version is available.</p>


https://github.com/kfamyn/whatnow/assets/102179774/90ec8a42-bb98-4026-b139-727a9ccd67af


# Used technologies

- [cURL](https://github.com/curl/curl)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Visual Crossing API](https://www.visualcrossing.com/weather-api)
- [Adobe Photoshop](https://www.adobe.com/products/photoshop.html), [Figma](https://www.figma.com)

# Installation

- [Download for Windows 10 x64](https://drive.google.com/drive/folders/1F6kvKCWHBaDPzXyZoUNG7M9hawGleJDz?usp=sharing)

# Setup for further development

### Windows

To contribute to the project, you will need to install [Qt Creator](https://www.qt.io/offline-installers) and clone a repository.

You can setup the project in Qt Creator by opening the Weather.pro file.

All the neccessary libraries are present in the repository.

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

Source design files can be found [here](). All the assets are stored and loaded into ```assets.qrc``` from /assets folder.

### Extending functionality

Following **SOLID** principles, the code is quite easy to extend. All the widget classes are encapsulateed and they are only dependant on ```weatherAPI``` class.
