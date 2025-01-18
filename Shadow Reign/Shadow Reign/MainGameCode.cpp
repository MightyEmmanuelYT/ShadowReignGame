#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <windows.h> // For changing console colors
#include <iomanip> // For formatting the summary table

using namespace std;

// Structs for Choices and Events
struct Choice {
    string description;
    bool isCorrect;
};

struct Event {
    string scenario;
    vector<Choice> choices;
};

// Function to set background color
void setBackgroundColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Typewriter effect function
void typewriter(const string& text, int delay = 50) {
    for (char c : text) {
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << endl;
}

// Handle multi-choice events
void handleEvent(const Event& event, int& correctChoices) {
    system("cls"); // Clear the screen
    cout << event.scenario << endl;

    for (size_t i = 0; i < event.choices.size(); ++i) {
        cout << i + 1 << ". " << event.choices[i].description << endl;
    }

    int choice;
    while (true) {
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            if (event.choices[choice - 1].isCorrect) {
                setBackgroundColor(10); // Green for correct
                cout << "Correct choice!\n";
                correctChoices++;
            }
            else {
                setBackgroundColor(12); // Red for incorrect
                cout << "That wasn't the best choice...\n";
            }
            this_thread::sleep_for(chrono::seconds(3));
            setBackgroundColor(7); // Reset color
            break;
        }
        else {
            cout << "Invalid choice. Please choose between 1 and 3." << endl;
        }
    }
    this_thread::sleep_for(chrono::seconds(1)); // Delay before next event
}

// Determine outcome of a mission
void determineOutcome(int correctChoices, int totalEvents, int& perfectWins, int& goodWins, int& badWins) {
    system("cls"); // Clear the screen
    cout << "Mission Results:\n";
    if (correctChoices == totalEvents) {
        typewriter("Perfect Win: You excelled in every scenario!", 40);
        perfectWins++;
    }
    else if (correctChoices >= totalEvents / 2) {
        typewriter("Good Win: You made it through, but there were some mistakes.", 40);
        goodWins++;
    }
    else {
        typewriter("Bad Loss: The mission was a failure. Learn from your mistakes.", 40);
        badWins++;
    }
    this_thread::sleep_for(chrono::seconds(3));
}

// Transition to the next mission
void transitionToNextMission() {
    system("cls");
    typewriter("-- Transitioning to the next mission... --", 50);
    this_thread::sleep_for(chrono::seconds(2));
}

// Handle multi-choice events
void handleDynamicEvent(Event& event, int& correctChoices, bool isWinning) {
    system("cls"); // Clear the screen
    cout << event.scenario << endl;

    for (size_t i = 0; i < event.choices.size(); ++i) {
        cout << i + 1 << ". " << event.choices[i].description << endl;
    }

    int choice;
    while (true) {
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            if (event.choices[choice - 1].isCorrect) {
                setBackgroundColor(10); // Green for correct
                cout << "Correct choice! Silas gains the upper hand!\n";
                correctChoices++;
            }
            else {
                setBackgroundColor(12); // Red for incorrect
                cout << "Wrong choice! Eclipse counters effectively!\n";
            }
            this_thread::sleep_for(chrono::seconds(2));
            setBackgroundColor(7); // Reset color
            break;
        }
        else {
            cout << "Invalid choice. Please choose between 1 and 3." << endl;
        }
    }
    this_thread::sleep_for(chrono::seconds(1)); // Delay before next event
}

// Mission One: Combat Training
void missionOne(int& perfectWins, int& goodWins, int& badWins) {
    setBackgroundColor(8); // Gray background
    typewriter("-- Combat Training --", 70);
    typewriter("Welcome to the combat training program. You will face a series of scenarios designed to test your decision-making skills.", 40);

    vector<Event> events = {
        {"An enemy charges at you with a sword. What do you do?",
         { {"Dodge to the left.", true},
           {"Parry the attack head-on.", false},
           {"Roll backward for distance.", false} }},

        {"You spot an enemy aiming at you from a distance. What's your move?",
         { {"Take cover behind a wall.", true},
           {"Charge straight at them.", false},
           {"Fire back immediately.", false} }},

        {"An enemy throws a grenade into your vicinity. What's your response?",
         { {"Kick the grenade away.", false},
           {"Dive behind nearby cover.", true},
           {"Try to throw it back.", false} }},

        {"You're surrounded by enemies. What do you do?",
         { {"Use a flashbang to disorient them.", true},
           {"Fight them off one by one.", false},
           {"Look for an opening and run.", false} }}
    };

    int correctChoices = 0;
    for (size_t i = 0; i < events.size(); ++i) {
        handleEvent(events[i], correctChoices);

        if ((i + 1) % 2 == 0) {
            cout << "\n-- Narration --\n";
            if (correctChoices == i + 1) {
                cout << "Silas moves with precision and skill, impressing his instructors.\n";
            }
            else {
                cout << "Silas struggles but pushes through, determined to improve.\n";
            }
            this_thread::sleep_for(chrono::seconds(3));
        }
    }

    determineOutcome(correctChoices, events.size(), perfectWins, goodWins, badWins);
    transitionToNextMission();
}

// Mission Two
void missionTwo(int& perfectWins, int& goodWins, int& badWins) {
    setBackgroundColor(3); // Light Aqua for a new atmosphere
    typewriter("-- Mission Two: The Syndicate's Hideout --", 70);
    typewriter("After completing training, Silas is summoned for his first real mission: infiltrating a Syndicate hideout.", 40);

    vector<Event> events = {
        {"You see a Syndicate guard patrolling. What do you do?",
         { {"Sneak past quietly.", true},
           {"Take them out silently.", false},
           {"Distract them with a noise.", false} }},

        {"You approach the Syndicate's hideout. What's your next move?",
         { {"Survey the area for more guards.", true},
           {"Rush into the building.", false},
           {"Set up a trap nearby.", false} }},

        {"Inside, you hear voices. What's your plan?",
         { {"Eavesdrop on their conversation.", true},
           {"Engage them in combat.", false},
           {"Retreat to plan further.", false} }},

        {"The leader spots you. What do you do?",
         { {"Try to reason with them.", false},
           {"Challenge them to a duel.", true},
           {"Use a smoke bomb to escape.", false} }}
    };

    int correctChoices = 0;
    for (size_t i = 0; i < events.size(); ++i) {
        handleEvent(events[i], correctChoices);

        if ((i + 1) % 2 == 0) {
            cout << "\n-- Narration --\n";
            if (correctChoices == i + 1) {
                cout << "Silas advances with skill and caution, staying ahead of his enemies.\n";
            }
            else {
                cout << "Silas faces challenges but remains steadfast in his mission.\n";
            }
            this_thread::sleep_for(chrono::seconds(3));
        }
    }

    determineOutcome(correctChoices, events.size(), perfectWins, goodWins, badWins);
    transitionToNextMission();
}

// Mission Three: Recruitment Drive
void missionThree(int& perfectWins, int& goodWins, int& badWins) {
    setBackgroundColor(5); // Purple for a recruitment vibe
    typewriter("-- Mission Three: Recruitment Drive --", 70);
    typewriter("Silas needs allies to dismantle the Syndicate. He has three candidates to choose from. Choose wisely.", 40);

    // Recruit profiles
    vector<string> profiles = {
        "1. Nyx (The Shadow Operative): A former Syndicate assassin specializing in stealth and sabotage.",
        "2. Orion (The Tech Prodigy): A genius hacker with unmatched technical skills.",
        "3. Kael (The War Veteran): A battle-hardened ex-mercenary with extensive combat experience."
    };

    for (const string& profile : profiles) {
        cout << profile << endl;
    }

    // Player chooses two recruits
    int choice1, choice2;
    while (true) {
        cout << "\nSelect your first recruit (1-3): ";
        cin >> choice1;
        cout << "Select your second recruit (1-3): ";
        cin >> choice2;

        if (choice1 >= 1 && choice1 <= 3 && choice2 >= 1 && choice2 <= 3 && choice1 != choice2) {
            break;
        }
        else {
            cout << "Invalid choices. Choose two different recruits between 1 and 3.\n";
        }
    }

    // Recruit conversation logic
    vector<Event> recruitEvents = {
        {"Nyx tests your tactical skills. What do you do?",
         { {"Outline a stealthy approach.", true},
           {"Suggest a direct attack.", false},
           {"Propose a decoy maneuver.", false} }},

        {"Nyx challenges your loyalty. How do you respond?",
         { {"Promise unwavering trust.", true},
           {"Focus on the mission.", false},
           {"Deflect her question.", false} }},

        {"Orion asks how you'll use his skills. Your reply?",
         { {"Hack Syndicate servers.", true},
           {"Lead field operations.", false},
           {"Work as backup support.", false} }},

        {"Orion jokes about leadership. What's your reaction?",
         { {"Play along.", true},
           {"Assert your authority.", false},
           {"Ignore him.", false} }},

        {"Kael tests your resolve. What do you say?",
         { {"Show determination.", true},
           {"Focus on logic.", false},
           {"Appeal to emotion.", false} }},

        {"Kael asks why you need him. Your response?",
         { {"Highlight his experience.", true},
           {"Emphasize teamwork.", false},
           {"Mention his combat skills.", false} }}
    };

    int recruitsJoined = 0;

    for (int recruit : {choice1, choice2}) {
        cout << "\n-- Conversation with " << profiles[recruit - 1] << " --\n";

        int correctChoices = 0;
        handleEvent(recruitEvents[(recruit - 1) * 2], correctChoices);
        handleEvent(recruitEvents[(recruit - 1) * 2 + 1], correctChoices);

        if (correctChoices == 2) {
            typewriter("They agree to join your team!", 40);
            recruitsJoined++;
        }
        else {
            typewriter("They decline your offer.", 40);
        }
    }

    // Determine outcome
    if (recruitsJoined == 2) {
        typewriter("Perfect Win: Both recruits join your team, strengthening your chances against the Syndicate.", 40);
        perfectWins++;
    }
    else if (recruitsJoined == 1) {
        typewriter("Good Win: One recruit joins your team. It's a step forward.", 40);
        goodWins++;
    }
    else {
        typewriter("Bad Loss: None of the recruits join. You must rethink your approach.", 40);
        badWins++;
    }

    transitionToNextMission();
}

// Mission Four: Silas vs. Eclipse
void missionFour(int& perfectWins, int& goodWins, int& badWins) {
    setBackgroundColor(1); // Dark blue for combat atmosphere
    typewriter("-- Mission Four: Silas vs. Eclipse --", 70);
    typewriter("Silas and Eclipse prepare to spar. This is no ordinary fight; they will push each other to the limit.", 40);

    vector<Event> events(6);
    int correctChoices = 0;

    for (size_t i = 0; i < events.size(); ++i) {
        bool isWinning = correctChoices > i / 2; // Determine if Silas is currently "winning"

        if (isWinning) {
            events[i] = { "Silas presses the attack. What does he do?",
                        { {"Launch a powerful punch.", true},
                          {"Go for a risky spinning kick.", false},
                          {"Step back to assess the situation.", false} } };
        }
        else {
            events[i] = { "Silas is on the defensive. What does he do?",
                        { {"Parry and counterattack.", true},
                          {"Dodge repeatedly to avoid damage.", false},
                          {"Retreat to gain space.", false} } };
        }

        handleDynamicEvent(events[i], correctChoices, isWinning);
    }

    // Determine fight outcome
    system("cls"); // Clear the screen
    cout << "Fight Results:\n";
    if (correctChoices >= 4) {
        typewriter("Victory! Silas triumphs over Eclipse with skill and determination.", 40);
        typewriter("Eclipse: \"You're incredible, Silas. I'll join your team without hesitation.\"");
        perfectWins++;
    }
    else {
        typewriter("Defeat. Eclipse proves to be the stronger fighter this time.", 40);
        typewriter("Eclipse: \"You fought well, Silas. But you still have room to grow. I'll consider joining you later.\"");
        badWins++;
    }

    this_thread::sleep_for(chrono::seconds(3));

    transitionToNextMission();

}

// Final Mission: Black Veil Syndicate
void finalMission(int& perfectWins, int& goodWins, int& badWins, bool hasEclipse, vector<string> recruitedMembers) {
    setBackgroundColor(4); // Red background for the final mission
    typewriter("-- Final Mission: The Fall of the Black Veil Syndicate --", 70);

    // Special scenario with recruited members
    if (!recruitedMembers.empty()) {
        typewriter("Your recruited members step up to assist you in a critical situation.", 50);
        for (const auto& member : recruitedMembers) {
            cout << member << " plays their role perfectly, aiding the team!\n";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    else {
        typewriter("Without any recruits, Silas must shoulder the burden alone.", 50);
    }

    // Events
    vector<Event> events;
    if (hasEclipse) {
        typewriter("Eclipse stands by your side, determined to see the Syndicate fall.", 50);
        events = {
            {"The Syndicate's guards are alerted. What's your move?",
             { {"Coordinate with Eclipse to flank them.", true},
               {"Charge head-on.", false},
               {"Set a trap.", false} }},

            {"You encounter a heavily armed Syndicate captain. What do you do?",
             { {"Let Eclipse engage while you provide support.", true},
               {"Fight the captain directly.", false},
               {"Attempt to negotiate.", false} }},

            {"The Syndicate leader activates a self-destruct mechanism. What's your move?",
             { {"Disable the mechanism together.", true},
               {"Escape immediately.", false},
               {"Try to destroy the control panel.", false} }}
        };
    }
    else {
        typewriter("Without Eclipse, the mission is even more dangerous.", 50);
        events = {
            {"The Syndicate's guards are alerted. What's your move?",
             { {"Sneak past quietly.", true},
               {"Charge head-on.", false},
               {"Set a trap.", false} }},

            {"You encounter a heavily armed Syndicate captain. What do you do?",
             { {"Distract and evade.", true},
               {"Fight the captain directly.", false},
               {"Attempt to negotiate.", false} }},

            {"The Syndicate leader activates a self-destruct mechanism. What's your move?",
             { {"Disable the mechanism yourself.", true},
               {"Escape immediately.", false},
               {"Try to destroy the control panel.", false} }}
        };
    }

    int correctChoices = 0;
    for (const auto& event : events) {
        handleEvent(event, correctChoices);
    }

    determineOutcome(correctChoices, events.size(), perfectWins, goodWins, badWins);

    // Ending Narration
    system("cls");
    cout << "-- Ending Narration --\n";
    if (correctChoices == events.size()) {
        typewriter("The Dawn of a New Era -\nSilas stood atop the ruins of the Black Veil Syndicate, the echoes of battle fading into the wind. \nHis team, forged through trials of trust and loyalty, stood with him—Eclipse at his side, their bond unbreakable. \nTogether, they had shattered the chains that bound the world in fear. \nSilas gazed at the horizon, the thought of his children filling him with a quiet pride. \nHe had done this for them—a world reborn, free of shadows. \nThis was his legacy, not as a warrior, but as a father. \nHe had given everything, and in return, had earned the future his children deserved. \nThe dawn was no longer a promise. \nIt was here.", 50);
    }
    else if (correctChoices >= events.size() / 2) {
        typewriter("A World Remade, but Not Whole -\nThe Black Veil Syndicate had fallen, its power dismantled, but the price of victory weighed heavily. \nSilas carried the weight of those he could not save, the allies he had not secured, and the mistakes he could not undo.The world was safer, but not yet healed.He returned to his children, knowing that his fight was not over, even if the battle had been won. \nThey were his beacon, the reason he endured every scar and sorrow.As he held them close, he made a solemn vow : the sacrifices made would not be in vain.He would keep pushing, keep striving, until the world matched the hope he saw in their eyes.", 50);
    }
    else {
        typewriter("A Father’s Unyielding Flame -\nThe Black Veil Syndicate emerged victorious, their grip on the world tighter than ever. \nSilas knelt amidst the wreckage of his mission, his heart heavy but unbroken. \nHe had failed, but the fire within him still burned.His children’s laughter, their innocent dreams, were too precious to surrender. \nThe road ahead would be darker and lonelier, but he would walk it.Silas rose from the ashes of defeat, his resolve steeled by love greater than any fear. \n“Not yet, ” he whispered to the shadows.For the sake of his children, for the hope of a brighter world, he would rise again—and this time, nothing would stop him.", 50);
    }

    // Display total scores
    cout << "\nYour Total Scores:\n";
    cout << "Perfect Wins: " << perfectWins << endl;
    cout << "Good Wins: " << goodWins << endl;
    cout << "Bad Wins: " << badWins << endl;
}

// Function to display the final summary
void displaySummary(int perfectWins, int goodWins, int badWins, int totalMissions) {
    system("cls");
    typewriter("-- Final Summary --", 70);

    cout << left << setw(20) << "Outcome" << setw(10) << "Count" << endl;
    cout << left << setw(20) << "Perfect Wins:" << setw(10) << perfectWins << endl;
    cout << left << setw(20) << "Good Wins:" << setw(10) << goodWins << endl;
    cout << left << setw(20) << "Bad Losses:" << setw(10) << badWins << endl;

    cout << "\nOverall Performance: ";
    if (perfectWins == totalMissions) {
        typewriter("Legendary Hero: Silas's performance is unmatched!", 40);
    }
    else if (goodWins >= badWins) {
        typewriter("Competent Agent: Silas has shown great promise but has room to grow.", 40);
    }
    else {
        typewriter("Rookie: Silas struggled, but every failure is a step toward growth.", 40);
    }
    this_thread::sleep_for(chrono::seconds(3));
}

int main() {
    int perfectWins = 0, goodWins = 0, badWins = 0;
    int totalMissions = 5;

    // Track Eclipse and recruited members
    bool hasEclipse = false; // Assume Eclipse isn't in the team initially
    vector<string> recruitedMembers;

    // Call each mission
    missionOne(perfectWins, goodWins, badWins);
    missionTwo(perfectWins, goodWins, badWins);
    missionThree(perfectWins, goodWins, badWins); // Pass recruited members to mission 3
    missionFour(perfectWins, goodWins, badWins);        // Update Eclipse's status in mission 4
    finalMission(perfectWins, goodWins, badWins, hasEclipse, recruitedMembers);

    // Display the summary of results
    displaySummary(perfectWins, goodWins, badWins, totalMissions);

    return 0;
}

