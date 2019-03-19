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
```javascript
let a = 1;

a = a + '1';

a // '11'
```

### Objects and Initializers:

Create objects using:
```javascript
let a  = {
   string: "string",
   number: 1,
   boolean: true,
   null: null
};
```

Objects properties can be both accessed using dot notation:
~~~~
a.propertyName
~~~~
or using bracket notation:
~~~~
a[propertyName]
~~~~

The spread operator '...' can be used to open objects and pick and copy properties from objects, especially if you want to copy objects that are immutable.

```javascript
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
```

### JS modules and imports

With ES6 you can import stuff from other .js files using the following syntax:

```javascript
import a from '.\iExportData';
```
Module imports can be done using:

```javascript
const app = require('express');
```
### Hoisting 

All declartions are moved to the beginning of their respective scopes. Functions go first, followed by variables. Note! Function expressions are **NOT** hoisted. 

```javascript
let foo = function bar(){
   ...
};
```
### Functions

Functions are values and can be passed around as such.

```javascript
let a = function b(){
   console.log('c');
}

let b = {
    d: "example",
    a : a
};

b // {d: "example", a: function b()}
b.a() // Logs 'c' to the console.

```
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

## React
React is structured kind of like a tree. Where the root of the tree is theroot component. Children (branches) are added as components. All components include a render function where the HTML of the component is set.
A child is added in the render function of their parent, and the childrens render functions are run almost recursivly.
Example:

```javascript
// This is the parent component.
const mayorKey = "you smart";
const anotherOne = "you loyal";

render(){
   <ChildComponent prop = {mayorKey}/>
   <AnotherChild iAmAlsoprop = {anotherOne} />
}
```
The render function is run whenever the `state` of the component is updated.

### State and props

#### Props
Props is a way of passing data from a parent from the parent component.
As seen in the example above the prop "prop" is passed from the parent component. The props are passed as an argument into the component's constructor, and later passed to the React.Component superclass. See example below:
```javascript
import React,  {Component} from "react";

export default class ChildComponent extends Component{
   constructor(props){
      super(props);
      // More constructor code
   }
   ...
}
```

Props are an essential part of passing data between components in React, which will be explained later.

State is a special object that contains that has the special function that every time it is updated the render function of the component whos state was updated is run. State needs to be updated using a special function called setState. Here is an example of updating a state to a default:

```javascript
resetForm(){
   let currState = this.state;
   Object.keys(currState).map(k => currState[k] = false);
   this.setState(currState);
}
```
### JSX
React uses JSX to easily combine HTML and JavaScript, which allows for expressions such as:

```javascript
const element = <p> You are a bold one! </p>;
```
This simplifies adding HTML content to the render functions.
Take for instance adding an unknown amount of list items to a list in html, it is not possible to hard code these into the HTML code, but since the structure of the items we can create an array of items which can be added to the render function without having to hard code HTML. See example below:

```javascript
render(){
   const usersNamedJames = fetch("https://localhost:3000/users").then(result => result.json()).then(r => r.filter(u => u.firstName === "James"));
   let list = usersNamedJames.map(u => <li> {u} </li>);
   return{
      <ul>
         {list}   
      </ul>
   }
}
```
Which for example could be rendered as the following HTML:

```html
<ul>
   <li> James Franco </li>
   <li> James Dean </li>
   <li> James McAvoy </li>
   <li> James Hetfield </li>
<ul> 
```
JSX code can be returned just as any other value.

```javascript
function makeIntoListItem(text){
   return <li> {text} </li>
}
```
Can even return entire Components. NOTE! Capitalization is required on user-defined components!

```javascript
function createComp(prop){
   return <StillFlying halfAShip = {prop} />
}
```
### Passing/Sharing data between react components

As we have seen earlier parent components can pass data to children using props. But how can children pass data to their parents?
The answer is yet again to use props!
By passing a callback function as a prop to the components and binding it to the parent component, later we can call the function through the props object. Ex:

 ```javascript export default class ParentComp extends Component {
   constructor(props){
      super(props);
      this.updateParentData = this.updateParentData.bind(this);
   }

   updateParentData(data){
      this.setState({myData: data});
   }

   render(){
      return(
         <div>
            <ChildComp callback = {(data) => this.updateParentData(data)} />
         </div>
      )
   }
} 
```
And in the child component data can now be passed to the parent component:

```javascript
export default class ChildComp extends Component {
   constructor(props){
      super(props);
      this.passData = this.passData.bind(this);
   }
   
   passData(e){
      this.props.callback(e.target.value);
   }
}
```
 
## Angular

## Web specific 
