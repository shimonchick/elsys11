using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SpellUIController : MonoBehaviour {

    [SerializeField]
    List<Button> buttons;

    private void Start()
    {
        for(int i = 0; i < buttons.Count; i++)
        {
            buttons[i].onClick.RemoveAllListeners();
            buttons[i].onClick.AddListener(() => FindObjectOfType<PlayerController>().CastSpell(i));
        }
    }
}
