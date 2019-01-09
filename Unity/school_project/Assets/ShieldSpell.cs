using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class ShieldSpell : Spell {

  


    [SerializeField]
    private Material shieldedShipMaterial;
    [SerializeField]
    private GameObject shieldPrefab;

    public float shieldTime = 2.0f;




    public override void Cast()
    {
        //Start();

        CreateShield();
        StartCoroutine(ChangeMaterial());


    }

    private IEnumerator ChangeMaterial()
    {
        Material oldMaterial = Caster.GetComponent<MeshRenderer>().material;
        Caster.GetComponent<MeshRenderer>().material = shieldedShipMaterial;
        Debug.Log("before waiting for seconds:" + shieldTime);
        yield return new WaitForSeconds(shieldTime);
        Debug.Log("should change material");
        Caster.GetComponent<MeshRenderer>().material = oldMaterial;
    }
    private void CreateShield()
    {
        GameObject shield = Instantiate(shieldPrefab, Caster.transform);
        Destroy(shield, shieldTime);
    
    }
}
