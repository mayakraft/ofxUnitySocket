using UnityEngine;
using System.Collections;
using SocketIO;
using System;

public class GameController : MonoBehaviour {

	public GameObject plane;

	// Use this for initialization
	void Start () {
		Debug.Log("starting app");
		GameObject go = GameObject.Find("SocketIO");
		SocketIOComponent socket = go.GetComponent<SocketIOComponent>();
		Debug.Log("searched for Socket IO");

		socket.On("message", TestMessage);
		socket.On("image", OnImageReceive);
	}
	public void TestMessage(SocketIOEvent e){
		Debug.Log("received message");
		Debug.Log(e.data);
	}

	public void OnImageReceive(SocketIOEvent e){
//		Debug.Log("received image");
		string b64string = e.data.ToString();
//		Debug.Log(b64string);
		b64string = b64string.Substring(1+23, b64string.Length-2-23);
//		b64string = b64string.Substring(1, b64string.Length-2);
//		Debug.Log(b64string);
		byte[] b64bytes = System.Convert.FromBase64String(b64string);
//		Debug.Log(b64bytes);

		Texture2D tex = new Texture2D(1, 1);
		tex.LoadImage(b64bytes);
		/*
		Debug.Log("width: " + tex.width);
		Debug.Log("height: " + tex.height);
		Color[] pixels = tex.GetPixels();
		for(int i = 0; i < tex.width; i++){
			for(int j = 0; j < tex.height; j++){
				Debug.Log(pixels[i+j*tex.width]);
			}
		}
		*/
		Material material = new Material(Shader.Find("Diffuse"));
		material.mainTexture = tex;
		plane.GetComponent<Renderer>().material = material;
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}