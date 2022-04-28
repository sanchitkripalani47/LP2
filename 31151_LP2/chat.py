import nltk
from nltk.chat.util import Chat, reflections

reflections = {
    "i am": "you are",
    "i was": "you were",
    "i": "you",
    "i'm": "you are",
    "i'd": "you would",
    "i've": "you have",
    "i'll": "you will",
    "my": "your",
    "you are": "I am",
    "you were": "I was",
    "you've": "I have",
    "you'll": "I will",
    "your": "my",
    "yours": "mine",
    "you": "me",
    "me": "you"
}


pairs = [
    [
        r"hi|hey|hello",
        ["Hello, How can I help you?"]
    ],
    [
        r"what is your name ?",
        ["I am a Quick Bot!"]
    ],
    [
        r"how are you ?",
        ["I'm doing good. How about You ?", ]
    ],
    [
        r"i am good",
        ["Nice to hear that, How can I help you?)", ]
    ],
    [
        r"(.*) available rooms|(.*) rooms available",
        ["We offer a double room and a single room. Which one would you like to know more about?"]
    ],
    [
        r"double room",
        ["It has a 2 rooms, can accomodate maximum of 4 people."]
    ],
    [
        r"single room",
        ["It has a 1 room, can accomodate maximum of 2 people."]
    ],
    [
        r"(.*) pool?",
        ["Yes", "Yes, it has a baby pool and a deep pool for adults."]
    ],
    [
        r"(.*) rates|(.*)rate",
        ["For which room would you like to know?"]
    ],
    [
        r"(.*) single room",
        ["It is Rs.2500/day"]
    ],
    [
        r"(.*) double room",
        ["It is Rs.4500/day"]
    ],
    [
        r"Is breakfast included?",
        ["Yes!", "Breakfast is complimentary"]
    ],
    [
        r"(.*) book a room?",
        ["Head over to the hotel's website or contact the reception"]
    ],
    [
        r"quit",
        ["BBye take care. See you soon :) ",
            "It was nice talking to you. See you soon :)"]
    ],
]


def chat():
    print("Hello, I am a Hotel Help Desk Chatbot!")
    chat = Chat(pairs, reflections)
    chat.converse()


# initiate the conversation
if __name__ == "__main__":
    chat()
