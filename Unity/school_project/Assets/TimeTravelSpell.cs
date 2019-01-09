using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeTravelSpell : Spell {


    [SerializeField]
    private float timeBack = 2.0f;
    [SerializeField]
    private GameObject TravelFx;
    [SerializeField]
    private float effectDuration = 1.0f;

    [SerializeField]
    private float effectScale = 5.0f;


    public override void Cast()
    {
        Debug.Log("casting time travel spell");
        
        
        try
        {
            Caster.transform.position = GameStateController.Instance.GetPositionAtTime(Time.time - timeBack);
            GameObject effect = Instantiate(TravelFx, Caster.transform);
            effect.transform.localScale *= effectScale;
            Debug.Log("effect created");
            Destroy(effect, effectDuration);
        }
        catch(System.Exception e)
        {
            Debug.Log("could not travel back in time");
        }
    }
}
