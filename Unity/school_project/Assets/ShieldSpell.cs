using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class ShieldSpell : Spell {

    
    private ShieldController shield;
    private PlayerController ship;

    [SerializeField]
    private Material shieldedShipMaterial;

    public float shieldTime = 2.0f;

    protected float cooldown = 7.0f;


    public override void Cast()
    {

        Debug.Log("casting shield");
        ship = FindObjectOfType<PlayerController>();
        if (!ship)
        {
            Debug.Log("ship not found");
        }
        shield = FindObjectOfType<ShieldController>();
        if (!shield)
        {
            Debug.Log("shield not found");
        }
        shield.ShowShield();
        ship.ChangeMaterial(shieldedShipMaterial);
            


    }


    //    private IEnumerator ShowShield()
    //    {
    //        shield.GetComponent<MeshRenderer>().enabled = true;
    //        shield.GetComponent<SphereCollider>().enabled = true;
    //        yield return new WaitForSeconds(shieldTime);
    //        shield.GetComponent<MeshRenderer>().enabled = false;
    //        shield.GetComponent<SphereCollider>().enabled = false;
    //
    //    }
}
