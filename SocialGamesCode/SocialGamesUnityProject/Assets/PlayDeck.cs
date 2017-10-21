using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//MAKE SURE TO TAG THE DECK AS "DECK" SO THE BOARD CAN REFERENCE TO IT
[System.Serializable]
public class PlayDeck : MonoBehaviour
{
    private Card[][] MainLand; //This is completely unaffected by a battle.
    private int AvailableIndex, GraveyardIndex; //DeckIndex = where the top of the deck is; AvailableIndex = how many cards the player has; Graveyard Index how many cards are in the Graveyard
    //private Card[] AvailableCards;
    private int[] AvailableCardsRows;
    public Card[] PlayerGraveyard;
    public Card[] Deck;
    public int MainLandWidth, MainLandHeight; //These two should equal to the mainland length

    // Use this for initialization
    void Start()
    {
        //Call Shuffle Function here
        //AvailableCards = new Card[MainLandWidth];
        AvailableCardsRows = new int[MainLandWidth];


    }

    public void UpdateAvailable()
    {
        for (int c = 0; c < MainLandWidth; c++)
        {
            int RowIndex = 0;
            for (int r = 0; r < MainLandHeight; r++)
            {
                if (MainLand[r][c].Name == "")
                {
                    RowIndex = r + 1;
                }
            }
            AvailableCardsRows[c] = RowIndex;
            print(AvailableCardsRows[c]);
        }
    }
    public bool IsPlayable(int row, int col)
    {
        return AvailableCardsRows[col] == row;
    }
    //returns the info of the card based on the index in the players hand and gets rid of it from your hand and places it in Graveyard
    public Card PlayCard(int index)
    {
        if(AvailableCardsRows[index] != MainLandHeight)
        {
            MainLand[AvailableCardsRows[index]][index].IsRevealed = false;
            Card Temporary = MainLand[AvailableCardsRows[index]][index];
            Destroy(MainLand[AvailableCardsRows[index]][index].Image);
            MainLand[AvailableCardsRows[index]][index] = getNullCard();
            print(MainLand[AvailableCardsRows[index]][index]);
            UpdateAvailable();
            Temporary.HasMadeMove = true;
            return Temporary;
        }
        else
        {
            return getNullCard();
        }
    }
    //draws card from the top of deck into AvailableCards
    public Card getNullCard()
    {
        Card NewCard = new Card("", null, 0, 0, 0, 0, 0, 0, false);
        return NewCard;
    }
    public void SpawnMainLand(float xPos, float yPos, float xSep, float ySep, int decker)
    {
        MainLand = new Card[MainLandHeight][];
        for (int i = 0; i < MainLandHeight; i++)
        {
            MainLand[i] = new Card[MainLandWidth];
            for (int j = 0; j < MainLandWidth; j++)
            {
                MainLand[i][j] = Deck[MainLandWidth * i + j];
                MainLand[i][j].Deck = decker;
                //print(MainLand[i][j].Name);
            }
        }
        //for testing stuff
        GraveyardIndex = 0;
        PlayerGraveyard = new Card[Deck.Length];
        for (int i = 0; i < MainLand.Length; i++)
        {
            PlayerGraveyard[i] = getNullCard();
        }
        for (int r = 0; r < MainLandHeight; r++)
        {
            for(int c = 0; c < MainLandWidth; c++)
            {
                //print("This should be fucking instantiating stuff");
                print(MainLand[r][c].Name);
                //Instantiates all the GameObjects its been holding and use its reference to point to it.
                MainLand[r][c].Image = Instantiate(MainLand[r][c].Image, new Vector3(xPos + xSep * c, yPos - ySep * r, 0), Quaternion.identity) as GameObject;
                MainLand[r][c].IsRevealed = true;
                MainLand[r][c].UpdateCard();
            }
        }
    }
}
[System.Serializable]
public class Card
{
    public string Name;
    public GameObject Image;
    public int Attack;
    public int Health;
    public int Effect;
    public int IslandSize;
    public int MovementDistance;
    public int Deck;
    public bool IsRevealed;
    public bool HasMadeMove = false;

    public Card(string aName, GameObject aImage, int aAttack, int aHealth, int aEffect, int aIslandSize, int aMovementDistance, int aDeck, bool aIsRevealed)
    {
        Name = aName;
        Image = aImage;
        Attack = aAttack;
        Health = aHealth;
        Effect = aEffect;
        IslandSize = aIslandSize;
        MovementDistance = aMovementDistance;
        IsRevealed = aIsRevealed;
        Deck = aDeck;
    }
    //These accessor functions are pretty useless cuz this is a public class with public variables
    public string getCardName()
    {
        return Name;
    }
    public GameObject getCardSprite()
    {
        return Image;
    }
    public int getCardAttack()
    {
        return Attack;
    }
    public int getCardHealth()
    {
        return Health;
    }
    public int getCardEffect()
    {
        return Effect;
    }
    public int getCardIslandSize()
    {
        return IslandSize;
    }
    public int getCardMovementDistance()
    {
        return MovementDistance;
    }
    public int getCardDeck()
    {
        return Deck;
    }
    public bool getCardIsRevealed()
    {
        return IsRevealed;
    }
    public void UpdateCard()
    {
        Image.transform.GetChild(0).GetComponent<TextMesh>().text = Attack.ToString();
        Image.transform.GetChild(1).GetComponent<TextMesh>().text = Health.ToString();
        Image.transform.GetChild(2).GetComponent<TextMesh>().text = MovementDistance.ToString();
        if (IsRevealed)
        {
            Image.transform.GetChild(0).GetComponent<Renderer>().enabled = true;
            Image.transform.GetChild(1).GetComponent<Renderer>().enabled = true;
            Image.transform.GetChild(2).GetComponent<Renderer>().enabled = true;
        }
        else
        {
            Image.transform.GetChild(0).GetComponent<Renderer>().enabled = false;
            Image.transform.GetChild(1).GetComponent<Renderer>().enabled = false;
            Image.transform.GetChild(2).GetComponent<Renderer>().enabled = false;
        }
        if(Health <= 0)
        {
            //GameObject.Destroy(Image);
            Name = "";
        }
    }
    //returns 0 if no cards die
    //returns 1 if this card dies
    //returns 2 if the other card dies
    //return 3 if they both kill each other
    public int AttackOtherCard(ref Card other)
    {
        Health -= other.Attack;
        other.Health -= Attack;
        IsRevealed = true;
        other.IsRevealed = true;
        UpdateCard();
        other.UpdateCard();
        if (Health > 0 && other.Health > 0)
        {
            return 0;
        }
        else if(!(Health > 0) && other.Health > 0)
        {
            return 1;
        }
        else if (!(other.Health > 0) && Health > 0)
        {
            return 2;
        }
        return 3;
    }
    public void TempReveil()
    {
        Debug.Log("TempReveil");
        Image.transform.GetChild(0).GetComponent<Renderer>().enabled = true;
        Image.transform.GetChild(1).GetComponent<Renderer>().enabled = true;
        Image.transform.GetChild(2).GetComponent<Renderer>().enabled = true;
        HasMadeMove = false;
    }
}
