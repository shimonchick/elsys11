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
                Vector3 screenPosition = Camera.main.ScreenToWorldPoint(new Vector3(Screen.width, Screen.height, 0));
               
				asteroid.transform.position = new Vector3(Random.Range(0, screenPosition.x), 0, Random.Range(0, screenPosition.y));
				asteroid.transform.LookAt(target);
				
				Instantiate(asteroid);
				
				asteroids.Add(asteroid);

				Debug.Log("Asteroid created");
				
			}
            timePassed = 0;
        }
		timePassed += Time.deltaTime;
		foreach(GameObject a in asteroids)
		{
            float maxDistance = Random.Range(1, 10) * asteroidSpeed * Time.deltaTime;
			a.transform.position = Vector3.MoveTowards(a.transform.position, target.position, maxDistance);
		}
	}
}