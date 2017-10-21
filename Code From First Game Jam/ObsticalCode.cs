using UnityEngine;
using System.Collections;

public class ObsticalCode : MonoBehaviour
{

	// Use this for initialization
	void Start ()
    {
	
	}
	
	// Update is called once per frame
	void Update ()
    {
	
	}
    void OnCollisionEnter2D(Collision2D hit)
    {
        if (hit.gameObject.tag == "Player1" || hit.gameObject.tag == "Player2")
        {
            Destroy(gameObject);
        }
    }
}
