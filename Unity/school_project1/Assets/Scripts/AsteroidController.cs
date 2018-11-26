using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class AsteroidController : MonoBehaviour
{

	[SerializeField] private int spawnRate = 1; // 1 second
	// Use this for initialization
	[SerializeField] private int spawnCount = 1;
	[SerializeField] private GameObject[] asteroidPrefabs;
	[SerializeField] private Transform target;
	private List<GameObject> asteroids;
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (Time.deltaTime % spawnRate == 0)
		{
			
			GameObject asteroid = asteroidPrefabs[Random.Range(0, asteroidPrefabs.Length - 1)];
			int cameraHeight = Camera.main.pixelHeight;
			int cameraWidth = Camera.main.pixelWidth;
			Vector3 asteroidPosition = new Vector3();
			switch ((int)(Random.value * 4))
			{
				case 1:
					asteroidPosition.x = Random.Range(0, cameraWidth);
					asteroidPosition.z = 0;
					break;
				case 2:
					asteroidPosition.x = 0;
					asteroidPosition.z = Random.Range(0, cameraHeight);
					break;
				case 3 :
					asteroidPosition.x = Random.Range(0, cameraWidth);
					asteroidPosition.z = cameraHeight;
					break;
				case 4:
					asteroidPosition.x = cameraWidth;
					asteroidPosition.z = Random.Range(0, cameraHeight);
					break;
			}

			asteroidPosition.y = target.position.y;
			asteroid.transform.position = asteroidPosition;
			asteroid.transform.LookAt(target);
			Instantiate(asteroid);
			asteroids.Add(asteroid);
			
		}
		foreach(GameObject asteroid in asteroids)
		{
			asteroid.transform.posiction += asteroid.transform.forward * Time.deltaTime * Random.Range(1, 10);
		}
	}
}