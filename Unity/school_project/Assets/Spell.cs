using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class Spell : MonoBehaviour {

    public abstract void Cast();
    [SerializeField]
    protected float cooldown;

    [HideInInspector]
    public float currentCooldown = 0.0f;

    public float Cooldown
    {
        get
        {
            return cooldown;
        }

        set
        {
            cooldown = value;
        }
    }
}
