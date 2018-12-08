using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour {

    public float ShotsPerSecond = 10f;
    public GameObject ProjectileToSpawn;
    public Transform SpawnPosition;

    private float NextShotTime = 0.0f;
    
    public void Shoot()
    {
        float cooldown = 1 / ShotsPerSecond;

        if (Time.time > NextShotTime)
        {
            Instantiate(ProjectileToSpawn, SpawnPosition.position, SpawnPosition.rotation);
            NextShotTime = Time.time + cooldown;
        }
    }
}
