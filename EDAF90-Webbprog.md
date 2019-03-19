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

a = 1 + '1';

a // '11'
~~~~

### Objects and Initializers:

Create objects using:
'let a  = {};'

Objects properties can be both accessed using dot notation:
'a.propertyName'
or using bracket notation:
'a[propertyName]'


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

'const app = require('express');'

### Hoisting 

All declertions are moved to the beginning of their respectivescopes. Functions go first, followed by variables. Variables are also split up in declration and assignment. Note! Function expressions are **NOT** hoisted. 

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

## CSS

Describes and the *appearance/presentation* of the content.

## React

## Angular

## Web specific 
