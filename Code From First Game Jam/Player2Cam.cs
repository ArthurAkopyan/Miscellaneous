using UnityEngine;
using System.Collections;

public class Player2Cam : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
        transform.position = new Vector3(4.45f, GameObject.Find("Player2").transform.position.y+3.3f, -10);
    }
	
	// Update is called once per frame
	void Update ()
    {
        if (!GameObject.Find("Player2").GetComponent < Player2 > ().CameraLock)
        {
            transform.position = new Vector3(4.45f, GameObject.Find("Player2").transform.position.y + 3.45f, -10);
        }
        else
        {
            transform.position = new Vector3(4.45f, 147.9f, -10f);
        }
    }
}
