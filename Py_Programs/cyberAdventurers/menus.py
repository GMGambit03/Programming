from game import new_game_intro
from game import game_loop
import database

def clear_screen():
    print("\033[H\033[2J", end="")

def start_menu():
    while(True):
        clear_screen()

        print("")
        print("")

        print(" ==== Welcome to IDK at the moment ====")
        print("\n")
        print(" [ 1 ][ New Game ]")
        print(" [ 2 ][ Load Game ]")
        
        user_input = input(" : ")

        match user_input:
            case '1':
                player, game_state = new_game_intro()
                return player, game_state
            case '2':
                save_file_name = database.get_player_file()
                if save_file_name == False:
                    continue

                player = database.get_player(save_file_name)
                game_state = database.get_game_state(save_file_name)
                return player, game_state


         
def new_save_menu() -> str:
    while(True):
        clear_screen()

        print("")
        print("")
        print(" ==== IDK ====")
        print(" Player Name: ")

        user_input = input()

        if user_input[0].isdigit():
            print(" Name cannot have a number at the beginning")
            continue
        elif len(user_input) > 10:
            print(" Name cannot contain more then 20 charcters")
            continue

        break

    return user_input

def class_menu() -> dict:
    clear_screen()

    print("")
    print("")
    print(" [ [1] Barbarian ]                         [ [2] Mage ]                              [ [3] Assassin ]")
    print("\n")     
    print(" [ Health ]: 11                            [ Health ]: 3                             [ Health ]: 4")
    print(" [ Strength ]: 9                           [ Strength ]: 4                           [ Strength ]: 6")
    print(" [ Speed ]: 3                              [ Speed ]: 6                              [ Speed ]: 11")
    print(" [ Mana ]: 2                               [ Mana ]: 4                               [ Mana ]: 4")
    print("\n")     
    print(" Strength over subtlety.                   Power at a distance.                      Quick, quiet, deadly.")
    print(" You hit first talk later                  The universe is at your fingertips.       Gone before anyone notices")

    user_input = input()


    match user_input:
        case '1':
            player_data = database.class_data("Barbarian")
        case '2':
            player_data = database.class_data("Mage")
        case '3':
            player_data = database.class_data("Assassin")
    return player_data





