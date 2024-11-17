import random
import string

def generate_test_cases():
    test_cases = []
    
   
    empty_cases = [
        ("", "a"),
        ("", "ab"),
        ("", "abc"),
        ("", "abcd"),
        ("", "abcde"),
        ("a", ""),
        ("ab", ""),
        ("abc", ""),
        ("abcd", ""),
        ("abcde", "")
    ]
    test_cases.append(("EMPTY_STRINGS", empty_cases))
    
    
    repeated_cases = [
        ("aa", "aaa"),
        ("aaa", "aaaa"),
        ("aaaa", "aaaaa"),
        ("aaaaa", "aaaaaa"),
        ("aaaaaa", "aaaaaaa"),
        ("aaaaaaa", "aaaaaaaa"),
        ("aaaaaaaa", "aaaaaaaaa"),
        ("aaaaaaaaa", "aaaaaaaaaa"),
        ("aaaaaaaaaa", "aaaaaaaaaaa"),
        ("aaaaaaaaaaa", "aaaaaaaaaaaa")
    ]
    test_cases.append(("REPEATED_CHARACTERS", repeated_cases))
    
    # transposicion
    transpose_cases = [
        ("ab", "ba"),
        
        ("abcd", "badc"),
       
        ("abcdef", "badcfe"),
        
        ("abcdefgh", "badcfehg"),
        
        ("abcdefghij", "badcfehgji"),

        ("abcdefghijkl", "badcfehgjilk"),
        
    ]
    test_cases.append(("TRANSPOSITION_CASES", transpose_cases))
    
    
    equal_length_cases = [
        ("cat", "dog"),
        ("test", "best"),
        ("hello", "world"),
        ("python", "nodejs"),
        ("program", "changed"),
        ("function", "practice"),
        ("algorithm", "datatype"),
        ("computing", "databases"),
        ("processing", "diferentes"),
        ("development", "programming")
    ]
    test_cases.append(("EQUAL_LENGTH", equal_length_cases))
    
    
    different_length_cases = [
        ("a", "ab"),
        ("ab", "abc"),
        ("abc", "abcd"),
        ("abcd", "abcde"),
        ("abcde", "abcdef"),
        ("abcdef", "abcdefg"),
        ("abcdefg", "abcdefgh"),
        ("abcdefgh", "abcdefghi"),
        ("abcdefghi", "abcdefghij"),
        ("abcdefghij", "abcdefghijk")
    ]
    test_cases.append(("DIFFERENT_LENGTH", different_length_cases))
    
    
    pattern_cases = [
        ("ab", "cd"),
        ("aba", "cdc"),
        ("abab", "cdcd"),
        ("ababa", "cdcdc"),
        ("ababab", "cdcdcd"),
        ("abababa", "cdcdcdc"),
        ("abababab", "cdcdcdcd"),
        ("ababababa", "cdcdcdcdc"),
        ("ababababad", "cdcdcdcdcd"),
        ("abababababa", "cdcdcdcdcdc")
    ]
    test_cases.append(("PATTERN_CASES", pattern_cases))
    
   
    substring_cases = [
        ("al", "la"),
        ("alg", "log"),
        ("algo", "loga"),
        ("algor", "logar"),
        ("algori", "logari"),
        ("algorit", "logarit"),
        ("algorith", "logarith"),
        ("algorithm", "logarithm"),
        ("algorithms", "logarithms"),
        ("algorithmic", "logarithmic")
    ]
    test_cases.append(("SUBSTRING_CASES", substring_cases))
    
    
    insertion_cases = [
        ("a", "ab"),
        ("ab", "abc"),
        ("abc", "abcd"),
        ("test", "tests"),
        ("tests", "tested"),
        ("tested", "testing"),
        ("testing", "testings"),
        ("testings", "testinger"),
        ("testinger", "testingers"),
        ("testingers", "testingered")
    ]
    test_cases.append(("INSERTION_CASES", insertion_cases))
    
    
    deletion_cases = [
        ("ab", "a"),
        ("abc", "ab"),
        ("abcd", "abc"),
        ("abcde", "abcd"),
        ("abcdef", "abcde"),
        ("abcdefg", "abcdef"),
        ("abcdefgh", "abcdefg"),
        ("abcdefghi", "abcdefgh"),
        ("abcdefghij", "abcdefghi"),
        ("abcdefghijk", "abcdefghij")
    ]
    test_cases.append(("DELETION_CASES", deletion_cases))
    
   
    substitution_cases = [
        ("cat", "rat"),
        ("test", "best"),
        ("tests", "bests"),
        ("tested", "bested"),
        ("testing", "besting"),
        ("testings", "bestings"),
        ("testinger", "bestinger"),
        ("testingers", "bestingers"),
        ("testingered", "bestingered"),
        ("testingereds", "bestingereds")
    ]
    test_cases.append(("SUBSTITUTION_CASES", substitution_cases))
    
    def generate_random_string(length, char_set=string.ascii_lowercase):
        return ''.join(random.choice(char_set) for _ in range(length))
    
    
    small_random_cases = []
    for length in range(2, 12):
        str1 = generate_random_string(length)
        str2 = generate_random_string(length)
        small_random_cases.append((str1, str2))
    test_cases.append(("SMALL_RANDOM", small_random_cases))
    
    
    medium_random_cases = []
    for length in range(10, 30, 2):
        str1 = generate_random_string(length)
        str2 = generate_random_string(length)
        medium_random_cases.append((str1, str2))
    test_cases.append(("MEDIUM_RANDOM", medium_random_cases))
    
   
    large_random_cases = []
    for length in range(50, 150, 10):
        str1 = generate_random_string(length)
        str2 = generate_random_string(length)
        large_random_cases.append((str1, str2))
    test_cases.append(("LARGE_RANDOM", large_random_cases))
    
    def generate_biased_string(length):
        common_chars = 'aeiou'
        other_chars = 'bcdfghjklmnpqrstvwxyz'
        result = []
        for _ in range(length):
            if random.random() < 0.6:
                result.append(random.choice(common_chars))
            else:
                result.append(random.choice(other_chars))
        return ''.join(result)
    
    biased_cases = []
    for length in range(5, 25, 2):
        str1 = generate_biased_string(length)
        str2 = generate_biased_string(length)
        biased_cases.append((str1, str2))
    test_cases.append(("BIASED_DISTRIBUTION", biased_cases))
    
    return test_cases

def save_test_cases(filename):
    test_cases = generate_test_cases()
    with open(filename, 'w') as f:
        for category, cases in test_cases:
            f.write(f"=== {category} ===\n")
            for i, (str1, str2) in enumerate(cases, 1):
                f.write(f"# Case {i}\n")
                f.write(f"{str1}\n{str2}\n")
            f.write("\n")

save_test_cases("test_cases.txt")