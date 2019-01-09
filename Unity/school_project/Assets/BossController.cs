using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossController : Ship {

    [SerializeField]
    Transform target;
    [SerializeField]
    Weapon rageModeWeapon;
    [SerializeField]
    Material rageModeMaterial;
    
    [Range(0, 1)]
    public float rageModeHPMissing = 0.7f;

    private HitReceiver hitReceiver;



    private void Start()
    {
        hitReceiver = GetComponent<HitReceiver>();
    }
    private bool ShouldEnableRageMode()
    {
        if((float)hitReceiver.currentHits/ (float)hitReceiver.hitsToKill > rageModeHPMissing)
        {
            return true;
        }
        return false;
    }
    private void EnableRageMode()
    {
        Destroy(gameObject.GetComponent<Weapon>());
        GetComponent<MeshRenderer>().material = rageModeMaterial;
        Instantiate(rageModeWeapon, gameObject.transform);

    }
    private void Update () {

        //Vector2 direction = Random.insideUnitCircle;
        //GetComponent<Rigidbody>().MovePosition(direction * movementSpeed * Time.deltaTime);

        if (!target) return;
        LookTarget(target.position);

        if (ShouldEnableRageMode())
        {
            EnableRageMode();
        }

        Shoot();


	}
}
