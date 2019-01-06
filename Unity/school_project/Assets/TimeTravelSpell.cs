using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TimeTravelSpell : Spell {

    protected float cooldown = 7.0f;

    [SerializeField]
    private float timeBack = 2.0f;
    [SerializeField]
    private GameObject TravelFx;
    [SerializeField]
    private float effectDuration = 1.0f;

    public override void Cast()
    {
        Debug.Log("casting time travel spell");
        GameObject player = FindObjectOfType<PlayerController>().gameObject;
        
        try
        {
            player.transform.position = GameStateController.Instance.GetPositionAtTime(Time.time - timeBack);
            GameObject effect = Instantiate(TravelFx, player.transform);
            Destroy(effect, effectDuration);
        }
        catch(System.Exception e)
        {
            Debug.Log("could not travel back in time");
        }
    }
}
