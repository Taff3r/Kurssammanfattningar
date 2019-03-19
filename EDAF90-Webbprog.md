# Kurssammanfattning för EDAF90
## JavaScript (ES6)
### Datatypes and values

   * number
   * string
   * boolean
   * null

   - undefined
   - object
   - symbol

All variables can be declerade as either 'var', 'let', or 'const'. Since ES6, don't use var, ever. Just don't.

All variables have dynamic types, which means arrays can contain items of different types. Object properties can be added and deleted.

This also leads to black-magic such as:
~~~~
let a = 1;

a = a + '1';

a // '11'
~~~~

### Objects and Initializers:

Create objects using:
~~~~
let a  = {
   string: "string",
   number: 1,
   boolean: true,
   null: null
};
~~~~

Objects properties can be both accessed using dot notation:
~~~~
a.propertyName
~~~~
or using bracket notation:
~~~~
a[propertyName]
~~~~

The spread operator '...' can be used to open objects and pick and copy properties from objects, especially if you want to copy objects that are immutable.

~~~~
let a = {
   x: 100,
   y: 200,
   a: "I am a point in 2D, whoop de doo"
}; 

let b = {
   b : "hello world",
   ...a
};

b // {b: "hello world", x: 100, y: 200, a: "I am a point in 2D, whoop de doo"}
~~~~ 

### JS modules and imports

With ES6 you can import stuff from other .js files using the following syntax:

~~~~
import a from '.\iExportData';
~~~~

Module imports can be done using:

~~~~
const app = require('express');
~~~~

### Hoisting 

All declartions are moved to the beginning of their respective scopes. Functions go first, followed by variables. Note! Function expressions are **NOT** hoisted. 

~~~~
let foo = function bar(){
   ...
};
~~~~

### Functions

Functions are values and can be passed around as such.

~~~~
let a = function b(){
   console.log('c');
}

let b = {
    d: "example",
    a : a
};

b // {d: "example", a: function b()}
b.a() // Logs 'c' to the console.
~~~~
## HTML

Describes and defines the *content* of the webpage.

### Elements
Elements are defined by different tags.
Such as:
* <hx> Header. Where is a number, or nothing.  
* <p> Paragraph. 
* <table> Table.
* <ul> Unordered list.
* <li> List item in list.

### The DOM

The DOM (Document Object Model) is a programming API for HTML and XML documents. It defines the logical structure of documents. "Document" is used broadly. Everything in the DOM can be modified, changed, deleted, or added.

The DOM is structured much like a tree much like the HTML code, or rather a "forest" since there can be more than one tree.

Elements from the DOM can be accessed in JavaScript in many different manners. Here is an example:
 
~~~~
let img = document.getElementById("catPic");
~~~~


## CSS

Describes and the *appearance/presentation* of the content.

<img src = "https://images-na.ssl-images-amazon.com/images/I/61i-Tg4jpZL._SL1205_.jpg" />

It is really annoying to use, luckily some companies have developed alternatives. 

#### Bootstrap

Bootstrap works by importing stylesheets by linking to them in the header.
Later the classes from the stylesheets can be used, such as in the examplebelow.

```html
<head>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
</head>
<body>
   <div class="jumbotron">
      <h1 class="display-4"> Hello There! </h1>
   </div>
   <h2> GENERAL KENOBI! </h2>
</body>
```
#### Materials

Materials can be instlled through npm. And adds new component which can beused in a manner similar to normal html elements.

## Event handling
There are many different events that can be handled. eventListeners can be added in multiple manners, but most commonly is:

```html
<button onclick="alert("DONT TOUCH ME")"> DONT YOU DARE </button>
```
or in JS:

```javascript

let onClick = function(){
   console.log("Hello World!");
};

let button = document.getElementById("btn");
button.addEventListener("click", onClick);

```

## Bubbling and capturing
When we have multiple eventlistener nested into each other like in the example below:
   
```html
<form onclick="alert('form')">FORM
  <div onclick="alert('div')">DIV
    <p onclick="alert('p')">P</p>
  </div>
</form>

```
The events will "bubble up", so even you pressed the p-element all its parent elements will also run their onClick-events.
You can stop bubbling by calling event.stopPropagation().

Capturing is the "reverse" of bubbling, usually capturing is set to false by default when declaring the eventlistener. Capturing can be enabled by setting an extra option in the addEventListener function. See example below.
```javascript
button.addEventListener("click", onClick, {capture: true});
```


#### event.target
A parent can always get information on what exactly happend. By using event.target we can get the origin of the event.


###

## React

## Angular

## Web specific 
