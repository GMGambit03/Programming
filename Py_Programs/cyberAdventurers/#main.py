from menus import start_menu 
from Object_Classes import Player
from Object_Classes import GameState
from game import game_loop
#village function
#player class and object
#the differnet classes ex: mage, barbarian, assassin
# item database
# the looad up screen
            




def main() -> bool:
    player, game_state = start_menu()
    print(player + ":" + game_state)
    #game_loop(player, game_state)
    return 0

if __name__ == "__main__":
    main()