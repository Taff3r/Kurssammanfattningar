/**
 * 1a. lägg till reserve(1000) eller resize(1000) för att reservera minne till alla push_backs 
 *
 */


/**
 * 1b. move konstruktor, genom att "sno" datan ifrån temp variablen som ändå kommer att gå ur scope slipper man kopiera alla värden ifrån temp.
 *
 * Image(Image&& other) noexcept w{other.w}, h{other.h} pixels(other.pixels){
 *      other.pixels = 0; // nullptr
 * }
 */
