using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon3 : Weapon {

    [SerializeField]
    private float angle = 20.0f;

    private float NextShotTime = 0.0f;

    public override void Shoot()
    {
        float cooldown = 1 / ShotsPerSecond;

        if (Time.time > NextShotTime)
        {

            var firstProjectile = Instantiate(ProjectileToSpawn, SpawnPosition.position, SpawnPosition.rotation);
            var secondProjectile = Instantiate(ProjectileToSpawn, SpawnPosition.position, SpawnPosition.rotation);
            var thirdProjectile = Instantiate(ProjectileToSpawn, SpawnPosition.position, SpawnPosition.rotation);

            secondProjectile.transform.rotation *= Quaternion.Euler(0, angle, 0);
            thirdProjectile.transform.rotation *= Quaternion.Euler(0, -angle, 0);

            Physics.IgnoreCollision(gameObject.GetComponent<Collider>(), firstProjectile.GetComponent<Collider>());
            Physics.IgnoreCollision(firstProjectile.GetComponent<Collider>(), secondProjectile.GetComponent<Collider>());
            Physics.IgnoreCollision(firstProjectile.GetComponent<Collider>(), thirdProjectile.GetComponent<Collider>());

            Physics.IgnoreCollision(gameObject.GetComponent<Collider>(), secondProjectile.GetComponent<Collider>());
            Physics.IgnoreCollision(secondProjectile.GetComponent<Collider>(), firstProjectile.GetComponent<Collider>());
            Physics.IgnoreCollision(secondProjectile.GetComponent<Collider>(), thirdProjectile.GetComponent<Collider>());



            Physics.IgnoreCollision(gameObject.GetComponent<Collider>(), thirdProjectile.GetComponent<Collider>());
            Physics.IgnoreCollision(thirdProjectile.GetComponent<Collider>(), firstProjectile.GetComponent<Collider>());
            Physics.IgnoreCollision(thirdProjectile.GetComponent<Collider>(), secondProjectile.GetComponent<Collider>());

            NextShotTime = Time.time + cooldown;
        }
    }
}
