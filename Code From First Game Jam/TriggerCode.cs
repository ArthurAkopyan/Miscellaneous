using UnityEngine;
using System.Collections;

public class TriggerCode : MonoBehaviour
{
	public GameObject player1;
	public GameObject endpic;
	public GameObject text1,text2;
	public GameObject bgsong, victory;

	void Update(){
		if (player1.GetComponent<Player1> ().Win == 1) {
			endpic.SetActive(true);
			text1.SetActive(true);
			bgsong.SetActive(false);
			victory.SetActive(true);
		}
		else if (player1.GetComponent<Player1> ().Win == 2) {
			endpic.SetActive(true);
			text2.SetActive(true);
			bgsong.SetActive(false);
			victory.SetActive(true);
		}
	}

}