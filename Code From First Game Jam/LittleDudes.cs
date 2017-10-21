using UnityEngine;
using System.Collections;

public class LittleDudes : MonoBehaviour {

    // Use this for initialization
    int i;
	void Start ()
    { 
        transform.position = new Vector2(940f, 640f);
	}
	
	// Update is called once per frame
	void Update ()
    {
        //GameObject.Find("Player2").transform.position.y
        transform.position = new Vector2(940f, 640f+ (GameObject.Find("Player1").transform.position.y)*1.48f);
        i++;
    }
}
