// Icodemaker.h
// Codemaker Interface

// This interface represents all the operations that a Codemaker 
// should be able to do.

// Base class
template <class T>
class Codemaker {
    
    public:
        // The generate function creates a randomized set of items
        // based on the type of Codemaker desired
        void generate();

        // The checkCorrect function takes in a provided Codemaker 
        // and returns the number of items that are in the correct
        // location and of the correct value
        int checkCorrect(Codemaker<T> guess);

        // The checkIncorrect function takes in a provided Codemaker
        // and returns the number of items that are not in the
        // correct location but are of the correct value
        int checkIncorrect(Codemaker<T> guess);
    
}
