using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class AsteroidController : MonoBehaviour
{

	[SerializeField] private float spawnRate = 1; // 1 second
	// Use this for initialization
	[SerializeField] private int spawnCount = 1;
	[SerializeField] private GameObject[] asteroidPrefabs;
	[SerializeField] private Transform target;
	[SerializeField] private float asteroidSpeed = 1.0f;
	private List<GameObject> asteroids;
	private float timePassed = 0.0f;
	void Start () {
		asteroids = new List<GameObject>();
	}
	
	// Update is called once per frame
	void Update () {
		if (timePassed > spawnRate)
		{
			for(int i = 0; i < spawnCount; i++){
				GameObject asteroid = asteroidPrefabs[Random.Range(0, asteroidPrefabs.Length)];
				int cameraHeight = Camera.main.pixelHeight;
				int cameraWidth = Camera.main.pixelWidth;
				Vector3 asteroidPosition = new Vector3();
				switch (Random.Range(0, 4))
				{
					case 0:
						asteroidPosition.x = Random.Range(0, cameraWidth);
						asteroidPosition.z = 0;
						break;
					case 1:
						asteroidPosition.x = 0;
						asteroidPosition.z = Random.Range(0, cameraHeight);
						break;
					case 2 :
						asteroidPosition.x = Random.Range(0, cameraWidth);
						asteroidPosition.z = cameraHeight;
						break;
					case 3:
						asteroidPosition.x = cameraWidth;
						asteroidPosition.z = Random.Range(0, cameraHeight);
						break;
				}
                asteroidPosition = Camera.main.ScreenToWorldPoint(asteroidPosition);
                asteroidPosition.y = 0;
                asteroid.transform.position = asteroidPosition;

				asteroid.transform.LookAt(target);
				
				Instantiate(asteroid);
				
				asteroids.Add(asteroid);

				Debug.Log("Asteroid created");
				timePassed = 0;
			}
		}
		timePassed += Time.deltaTime;
		foreach(GameObject a in asteroids)
		{
            float maxDistance = Random.Range(1, 10) * asteroidSpeed * Time.deltaTime;
			a.transform.position =Vector3.MoveTowards(a.transform.position, target.position, maxDistance);
		}
	}
}