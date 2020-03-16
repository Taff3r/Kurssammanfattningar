/** 
 * 1a. Funktionen kommer inte att fungera korrekt, b i "return a + b" finns inte med i funktionens scope.
 * 1b. "Fångar" alla variabler i scope:t "by value" alltså genom kopia.
 * 1c. Odefinerat beteende för att när väl funktionen returneras från create_function kommer b ha lämnat sitt scope.
 */
