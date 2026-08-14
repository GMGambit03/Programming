import menus
from Object_Classes import Player
from Object_Classes import GameState

def new_game_intro():
    while(True):
        menus.clear_screen()
        
        print("")
        print("")

        print(" You wake up to shouting outside. The village square is full of lantern light and worried faces. ")
        print(" The Elder stands at the well's edge. The water inside has turned black")
        print("\n")
        print("\n")
        print(" **Elder**: The seal is failing. There's a passage east of here that wasn't open yesterday. It is now.")
        print("\n")
        print("[ 1 ]: I'll go take a look")
        print("[ 2 ]: What exactly is the 'seal'?")
        print("[ 3 ]: Why me?")

        user_input = input()
        
        menus.clear_screen()
        match user_input:
            case '1':
                print("")
                print("")

                print(" **Elder**: Good, before you go what's your name and class.")

                player_name = menus.new_save_menu()
                player_class = menus.class_menu()
                player = Player(player_class, player_name)

                game_state = GameState()
                game_state.intro_complete = True

                print(" **Elder**: Nice to have you stand and cure our village.")
                print(" **Elder**: Lets head to the first dungeon.")

                return player, game_state
            case '2':
                print("")
                print("")
                
                print(" **Elder**: Generations ago, something tore open beneath this village")
                print(" **Elder**: The Warden's Heart has kept it shut ever since.")
                print(" **Elder**: Until now")
                print("")
                print(" [ Enter any key to continue ]")
                input()
                continue
            case '3':
                print("")
                print("")

                print(" **Elder**: Because you're the only one standing here, and the rest of everyone else is sleep")
                print("")
                print(" [ Enter any key to continue ]")
                input()
                continue
            case _:
                print("")
                print("")

                print(" [ Please enter a valid response ]")
                print("")
                print(" [ Enter any key to continue ]")
                input()
                continue


                


def game_loop(player, gamestate):
    return 0
    
