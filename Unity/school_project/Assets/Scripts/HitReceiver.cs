using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HitReceiver : MonoBehaviour {
	public GameObject ObjectToSpawnOnDeath;
	public GameObject DestructionFX;
    public List<GameObject> HitFX;
	public float SpawnDistance = 2;
	public float DeflectionAngle = 45;
	public float DestructionFXDuration = 0.5f;
    public float HitFXDuration = 0.5f;
	public uint ScoreOnDeath = 0;
	public bool DebugDraw = false;
    public uint hitsToKill = 1;
    public float hitScale = 2.0f; 

    private uint currentHits = 0;



    public void ReceiveHit(GameObject damageDealer)
    {
        currentHits++;
        if (currentHits == hitsToKill)
        {
            if (ObjectToSpawnOnDeath != null)
            {
                Vector3 hitDirection = transform.position - damageDealer.transform.position;
                hitDirection.Normalize();
                if (DebugDraw)
                {
                    Debug.DrawLine(damageDealer.transform.position, transform.position, Color.red, 2.0f);
                }
                SpawnDeathObject(hitDirection, -DeflectionAngle);
                SpawnDeathObject(hitDirection, DeflectionAngle);
                if (gameObject.tag == "Asteroid")
                {
                    GameStateController.Instance.CurrentAsteroids += 2;
                }
            }
            if (DestructionFX != null)
            {
                GameObject spawnedFX = Instantiate(DestructionFX, transform.position, Random.rotation);
                Destroy(spawnedFX, DestructionFXDuration);
            }
            
            if(gameObject.tag == "Asteroid")
            {
                GameStateController.Instance.CurrentAsteroids -= 1;
            }
            GameStateController.Instance.IncrementScore(ScoreOnDeath);
            Destroy(gameObject);
        }
        if (HitFX.Count != 0)
        {
            Debug.Log("should show effect");
            GameObject spawnedFX = Instantiate(HitFX[Random.RandomRange(0,HitFX.Count)], transform.position, Random.rotation);
            spawnedFX.transform.localScale *= hitScale;
            Destroy(spawnedFX, HitFXDuration);
        }
    }

    

	private void SpawnDeathObject(Vector3 hitDirection, float angle)
	{
		Vector3 spawnDirection = Quaternion.AngleAxis (angle, Vector3.up) * hitDirection;
		Vector3 spawnPosition = transform.position + spawnDirection * SpawnDistance;
		if (DebugDraw) {
			Debug.DrawLine (transform.position, spawnPosition, Color.green, 2.0f);
		}

		GameObject spawnedObject = Instantiate(ObjectToSpawnOnDeath, spawnPosition, Random.rotation);
		var asteroidMovementController = spawnedObject.GetComponent<AsteroidMovementController> ();
		if (asteroidMovementController) {
			asteroidMovementController.InitialDirection = spawnDirection;
		}
	}
}
